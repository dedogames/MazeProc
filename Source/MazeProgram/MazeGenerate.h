/*

	Project: Name of Project
	Developer: Gelson G. Rodrigues
	Date: 05-10-2019

	***************
	* Description *
	***************

	This class Create a procedural maze using backtracking algorithm
	I use this book to reference
	https://www.amazon.com.br/Procedural-Content-Generation-Development-English-ebook/dp/B0158OZ8A4

	Based on NxN grid the algorithm recursively create a path with start point(MazeItem) and finish point(MazeItem)
	The path is empty and the walls are blocks(MazeItem)

	I create 2 rooms with 3x3 columns


	IMPORTANT: This maze is a NxN square


	************************
	*  Needs to be fixed   *
	************************

	   When N(size of the grid) is pair(N%2=0) to Walls aren't spawned and player can walk outside the maze,
	   temporarily I check if(size of grid == pair) size of grid += 1;


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
#include "MazeGenerate.generated.h"


UCLASS()
class MAZEPROGRAM_API AMazeGenerate : public AActor
{
	GENERATED_BODY()
	
public:	 
	AMazeGenerate();


    /* Player to set on Editor  Blueprints/BP_PlayerCharacter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UClass	 * Player;

	/*
		Destroy self and destroy Player
	*/
	UFUNCTION(BlueprintCallable, Category = "Maze")
	void Release();
	UFUNCTION(BlueprintImplementableEvent, Category = "Maze")
	void RestartGame();


	UPROPERTY(EditAnywhere, meta = (ClampMin = "5", ClampMax = "100", UIMin = "5", UIMax = "100"), Category = "MazeConfig")
		int GRID_WIDTH;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "5", ClampMax = "100", UIMin = "5", UIMax = "100"), Category = "MazeConfig")
		int GRID_HEIGHT;
	   
	UFUNCTION(BlueprintCallable, Category = "Maze")
		void SetSize(int GWidth, int GHeight);


	/* Start game from Widget */
	UFUNCTION(BlueprintCallable, Category = "Maze")
		void PlayGame();
 




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Maze")
	class APlayerCharacter * PlayerCharacter;	
	class UChildActorComponent* MainChildCp;
 

private:
	/* Functions to create a Maze*/
	bool TileIsValid(int column, int row);
	void CreatePath(int columnIndex, int rowIndex);
	void CreateRooms(int roomCount);
	void GenerateLevel();
 
	UPROPERTY()
	int TILE_SIZE;


	/*
		
		Meshes used to create a maze are inside the class AMazeItem
		StaticMesh'/Game/Maze/Floor.Floor'
		StaticMesh'/Game/Maze/Finish.Finish'
		StaticMesh'/Game/Maze/SM_Maze.SM_Maze' 
		StaticMesh'/Game/Maze/Finish.Finish'
		StaticMesh'/Game/Maze/sTART.start'

	*/
	TArray<TArray<class AMazeItem*>> m_grid;
	
};
