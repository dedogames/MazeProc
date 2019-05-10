/*

	Project: Name of Project
	Developer: Gelson G. Rodrigues
	Date: 05-10-2019

	***************
	* Description *
	***************

	Load meshes inside array to use on MazeGenerate.cpp


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

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeItem.generated.h"

/* kinds of Tiles 
	EMPTY = No Mesh
*/
enum ETile : uint8 {
	EMPTY,
	WALL,
	FLOOR,
	START, /* SM_START*/
	FINISH, /* SM_FINISH*/
};

UCLASS()
class MAZEPROGRAM_API AMazeItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeItem();
	void SetPosition(FVector Pos, int r=-1, int c=-1);
	FVector GetActorLocation();
	void SetMesh(ETile Tex);
	void SetScale(FVector Scale);
	void virtual BeginPlay() override;
	bool IsFinshed;

public:	
 
	int columnIndex;
	int rowIndex;
	class UBoxComponent* BoxCp;
	class UStaticMeshComponent * Sprite;
	FVector LocationTile;
	ETile	TypeTile;
	/*
		Load a Mesh and the key of map is your Type
	*/
	TMap<ETile, UStaticMesh*> Tiles;

	/* When Collide with Player Restart Game*/
	UFUNCTION()
	void OnOverlapCP(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
