// Fill out your copyright notice in the Description page of Project Settings.

 

#include "IsometricCamera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

AIsometricCamera::AIsometricCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	GetCameraComponent()->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	GetCameraComponent()->SetProjectionMode(ECameraProjectionMode::Perspective);
}

void AIsometricCamera::BeginPlay() {
	Super::BeginPlay();
}
void AIsometricCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FollowPlayer();
}

void AIsometricCamera::FollowPlayer()
{
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) )
	{
		FVector NewLoc = GetActorLocation() + UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCapsuleComponent()->GetComponentLocation();	 

		GetCameraComponent()->SetWorldLocation(NewLoc);
	}
}
