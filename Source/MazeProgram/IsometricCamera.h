/*

	Project: Name of Project
	Developer: Gelson G. Rodrigues
	Date: 05-10-2019

	***************
	* Description *
	***************

	Camera Fallow Player without rotation

	 
	************************
	*    Improvements	   *
	************************



	************************
	*    Changes   	       *
	************************

	Date		 Developer			Description
	--------------------------------------------------


*/

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "IsometricCamera.generated.h"

 
UCLASS()
class MAZEPROGRAM_API AIsometricCamera : public ACameraActor
{
	GENERATED_BODY()
public:
	AIsometricCamera();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void FollowPlayer();
};
