/*

	Project: Name of Project
	Developer: Gelson G. Rodrigues
	Date: 05-10-2019

	***************
	* Description *
	***************

	This class represent a redundancy of MazeItem


	************************
	*    Improvements	   *
	************************
    Create a basic  GameItem and all static actors(cube, targets..)
	will inherit from GameItem

	Encapsulate fields

	************************
	*    Changes   	       *
	************************



	Date		 Developer			Description
	--------------------------------------------------


*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetsActor.generated.h"

enum ETarget : uint8 {
	TSTART,
	TFINISH
};


UCLASS()
class MAZEPROGRAM_API ATargetsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetsActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void SetPosition(FVector Pos);
	void SetMesh(ETarget Tex); 



	class UBoxComponent* BoxTriggerCP; 
	TMap<ETarget, UStaticMesh*> Targets;
	FVector LocationTile;
	ETarget	TypeTile;

	class UStaticMeshComponent * Sprite;
};
