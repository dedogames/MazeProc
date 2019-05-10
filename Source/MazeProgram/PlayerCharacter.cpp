// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "IsometricCamera.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObject(TEXT("SkeletalMesh'/Game/TestAssets/Player/Meshes/SK_player.SK_player'"));
	if (MeshObject.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshObject.Object);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(37.0f);
	GetCapsuleComponent()->SetCapsuleRadius(20.0f);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//Pitch Yaw Roll
	CameraBoomComponent->SetupAttachment(RootComponent);
	CameraBoomComponent->SetRelativeRotation(FRotator(-45.0f, 125.0f, 0.0f));
	CameraBoomComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CameraBoomComponent->TargetArmLength = 600.0f;
	CameraBoomComponent->SocketOffset = FVector(0.0f, 0.0f, 20.0f);
	CameraBoomComponent->bDoCollisionTest = false;
	CameraBoomComponent->bInheritPitch = false;
	CameraBoomComponent->bInheritYaw = true;
	CameraBoomComponent->bInheritRoll = false;
	CameraBoomComponent->bUsePawnControlRotation = true;
	 
	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);
	FollowCameraComponent->SetFieldOfView(90.0f);
	FollowCameraComponent->SetupAttachment(CameraBoomComponent);
	FollowCameraComponent->bUsePawnControlRotation = true;

}

void APlayerCharacter::MouseYawInput(float Val)
{
	if( CurrentCamera == ETypeCamera::E3RDCamera)
		Super::AddControllerYawInput(Val); 
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	 

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	EnableInput(PC);
	CurrentCamera = ETypeCamera::E3RDCamera;
	PC->SetViewTargetWithBlend(FollowCameraComponent->GetAttachmentRootActor(), 0.5f);
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}
 

void APlayerCharacter::MoveForward(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Value %f:"), Value);
	if ((Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

		if ((CurrentCamera == ETypeCamera::EFixCamera))
		{
			if (Value > 0) {
				RotPlayer = FRotator(GetActorRotation().Pitch, 0.0f, GetActorRotation().Roll);

			}
			else {
				RotPlayer = FRotator(GetActorRotation().Pitch, 180.0f, GetActorRotation().Roll);
			}
		}
	}
}

void APlayerCharacter::MoveRight(float Value)
{

	if ((Value != 0.0f) && (CurrentCamera == ETypeCamera::EFixCamera))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); ;
		// add movement in that direction
		AddMovementInput(Direction, Value);

		//AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
		if (Value > 0) {
			RotPlayer = FRotator(GetActorRotation().Pitch, 90.0f, GetActorRotation().Roll);
			 
		}
		else {
			RotPlayer = FRotator(GetActorRotation().Pitch, -90.0f, GetActorRotation().Roll);
			 
		}
			
	}
		
}
 

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (  (CurrentCamera == ETypeCamera::EFixCamera))
	   SetActorRotation(RotPlayer);
}

 


void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
 
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight); 
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::MouseYawInput); 
	PlayerInputComponent->BindAction("ChangeCamera", IE_Pressed, this, &APlayerCharacter::ChangeCamera);

}

/*

	Press Tab


	Player can change to 
	ETypeCamera::E3RDCamera
		Only behind the player and rotate with mouse
	ETypeCamera::EFixCamera
		Follow the player but no rotate with player
		 

*/
void APlayerCharacter::ChangeCamera()
{
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<AActor*> FixedCameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIsometricCamera::StaticClass(), FixedCameraActors);
	CurrentCamera = (CurrentCamera == ETypeCamera::E3RDCamera) ? ETypeCamera::E3RDCamera  : ETypeCamera::EFixCamera;

	if (CurrentCamera == ETypeCamera::E3RDCamera)
	{
		CurrentCamera = ETypeCamera::EFixCamera;
		PlayerController->SetViewTargetWithBlend(FixedCameraActors[0], 0.3f);
		RotPlayer = FRotator(GetActorRotation().Pitch, 0.0f, GetActorRotation().Roll);
	}
	else {
		CurrentCamera = ETypeCamera::E3RDCamera;
		PlayerController->SetViewTargetWithBlend(FollowCameraComponent->GetAttachmentRootActor(), 0.3f);
	}



}

