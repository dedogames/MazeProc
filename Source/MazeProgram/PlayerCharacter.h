/*

	Project: Name of Project
	Developer: Gelson G. Rodrigues
	Date: 05-10-2019

	***************
	* Description *
	***************

	The Pawn can move on maze and change de camera with keyboard.
	The player can change camera to 3rd and use keyboard and mouse or
	use a fixed camera use only keyboard


	************************
	*    Improvements	   *
	************************

	Shooting
	Pickup Itens


	************************
	*    Changes   	       *
	************************

	Date		 Developer			Description
	--------------------------------------------------


*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


UENUM()
enum class ETypeCamera : uint8 {

	EFixCamera,
	E3RDCamera,
};
UCLASS(config = Game)
class MAZEPROGRAM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Camera")
		class UCameraComponent* IsometricCamera;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent * CameraBoomComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent * FollowCameraComponent;
 

	 

protected:

	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "left right turn addyaw"))
	void MouseYawInput(float Val);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	UFUNCTION()
		void MoveForward(float Value);

	/** Called for side to side input */
	UFUNCTION()
		void MoveRight(float Value);

 
	
private:



	UFUNCTION()
		void ChangeCamera();

	ETypeCamera CurrentCamera;
	FRotator RotPlayer;
	




	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FixedCamera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent * TopDownCameraCp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TopCamera, meta = (AllowPrivateAccess = "true"))
//		class UCameraComponent * TopDownCameraCp;



};
