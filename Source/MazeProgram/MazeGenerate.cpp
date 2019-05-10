// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGenerate.h"
#include "Components/ChildActorComponent.h"
#include "MazeItem.h"
#include <algorithm>
#include "TargetsActor.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ConstructorHelpers.h"
#include "MazeGameInstance.h"

// Sets default values
AMazeGenerate::AMazeGenerate()
{ 
	TILE_SIZE   = 50; 
	//Minimun value of grid
	GRID_WIDTH = 5;
	GRID_HEIGHT = 5;

	/* Join all cubes and MazeItem inside onde component*/
	MainChildCp = CreateDefaultSubobject<UChildActorComponent>(TEXT("MainChild"));
	RootComponent = MainChildCp;

	
	m_grid.SetNum(GRID_WIDTH);	 
}


/*
	Check if isn't a border
*/
bool AMazeGenerate::TileIsValid(int column, int row)
{
	bool validColumn, validRow;

	validColumn = ((column >= 0) && (column < GRID_WIDTH));
	validRow = ((row >= 0) && (row < GRID_HEIGHT));

	return (validColumn && validRow);
}



 
 

 

 

void AMazeGenerate::Release()
{
	Destroy();
	PlayerCharacter->Destroy();

}

// Called when the game starts or when spawned
void AMazeGenerate::BeginPlay()
{
	Super::BeginPlay(); 
}


/*
	Awalays create a Random maze based on initial value set before play
*/
void AMazeGenerate::PlayGame()
{ 
	/* Save value on memory because this object will be destroyed when 
		player find a finish target.
	*/
	((UMazeGameInstance*)UGameplayStatics::GetGameInstance(GetWorld()))->Grid_Size = GRID_WIDTH;
		m_grid.SetNum(GRID_WIDTH);
		GenerateLevel();
		/* Only 2 Rooms*/
	    CreateRooms(2); 
}


/*
	This algorithm is simillary to the book reference Chapter 9

		 Create a simple grid

		 0 = empty or no wall
		 - = Wall

		 7x7 grid

		 - 0 - 0 - 0 -
		 - 0 - 0 - 0 -
		 - 0 - 0 - 0 -
*/

void AMazeGenerate::GenerateLevel()
{
	if (GRID_WIDTH < 5) GRID_WIDTH = 5;
	if (GRID_HEIGHT < 5) GRID_HEIGHT = 5;
	// Create the initial grid pattern.
	for (int i = 0; i < GRID_WIDTH; ++i)
	{

		m_grid[i].SetNum(GRID_WIDTH);
		for (int j = 0; j < GRID_HEIGHT; ++j)
		{
			UChildActorComponent* NewComp1 = NewObject<UChildActorComponent>(this);
			NewComp1->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			NewComp1->bEditableWhenInherited = true;
			//NewComp1->SetWorldLocation(FVector(TILE_SIZE *i, TILE_SIZE * j, 0.0f));
			NewComp1->SetupAttachment(MainChildCp);
			NewComp1->RegisterComponent();
			NewComp1->SetChildActorClass(AMazeItem::StaticClass());

			m_grid[i][j] = (AMazeItem*)NewComp1->GetChildActor();
			FVector NewLocation;
			if ((i % 2 != 0) && (j % 2 != 0))
			{

				// Odd tiles, nothing. 
				m_grid[i][j]->SetMesh(ETile::EMPTY);
				NewLocation = FVector(TILE_SIZE *i, TILE_SIZE * j, 0.0f);
			}
			else
			{
				m_grid[i][j]->SetMesh(ETile::WALL);
				NewLocation = FVector(TILE_SIZE *i, TILE_SIZE * j, 25.0f);
			}

			// Set the position. 
			m_grid[i][j]->SetPosition(NewLocation, i, j);


		}
	}



	// Create the initial grid pattern.
	for (int i = 0; i < GRID_WIDTH; ++i)
	{
		// Make the first call to CarvePassage, starting the recursive

		CreatePath(1, 1);
	}


}

/*
	Step 2
	Create Random path insde grid minus borders wall
*/
void AMazeGenerate::CreatePath(int columnIndex, int rowIndex)
{
	// Store the current tile.
	AMazeItem** currentTile = &m_grid[columnIndex][rowIndex];
	// Create a list of possible directions and sort randomly.
	FVector2D directions[] = { { 0, -2 }, { 2, 0 }, { 0, 2 }, { -2, 0   } };
	std::random_shuffle(std::begin(directions), std::end(directions));

	// For each direction.
	for (int i = 0; i < 4; ++i)
	{
		// Get the new tile position.
		int dx = (*currentTile)->columnIndex + directions[i].X;
		int dy = (*currentTile)->rowIndex + directions[i].Y;
		// If the tile is valid.
		if (TileIsValid(dx, dy))
		{
			//Scale 0.05
			//Location -22

			// Store the tile.
			AMazeItem** tile = &m_grid[dx][dy];
			// If the tile has not yet been visited.
			if ((*tile)->TypeTile == ETile::EMPTY)
			{
				// Mark the tile as floor.
				(*tile)->SetMesh(ETile::FLOOR);
				(*tile)->SetScale(FVector(1.0, 1.0f, 0.03f));
				(*tile)->SetPosition(FVector((*tile)->GetActorLocation().X, (*tile)->GetActorLocation().Y, 0.0f));
				// Knock that wall down.
				int ddx = (*currentTile)->columnIndex + (directions[i].X / 2);
				int ddy = (*currentTile)->rowIndex + (directions[i].Y / 2);

				AMazeItem** wall = &m_grid[ddx][ddy];
				(*wall)->SetMesh(ETile::FLOOR);
				(*wall)->SetScale(FVector(1.0, 1.0f, 0.03f));
				(*wall)->SetPosition(FVector((*wall)->GetActorLocation().X, (*wall)->GetActorLocation().Y, 0.0f));
				// Recursively call the function with the new tile.
				CreatePath(dx, dy);
			}
		}
	}
}
/*
	Step 3
	And finally remove some blocks and create a empty room with finish target and start 
*/
void AMazeGenerate::CreateRooms(int roomCount)
{

	int roonsPos[][2] = {
		{1,1},
		{GRID_WIDTH - 4,GRID_HEIGHT - 4},

	};

	ETile tiles[2] = { ETile::START, ETile::FINISH };
	ETarget targets[2] = { ETarget::TSTART, ETarget::TFINISH };

	int roomWidth = 3; //std::rand() % 2 + 1;
	int roomHeight = 3; //std::rand() % 2 + 1;


	for (int i = 0; i < roomCount; i++)
	{

		UChildActorComponent* NewComp1 = NewObject<UChildActorComponent>(this);
		NewComp1->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		NewComp1->bEditableWhenInherited = true;
		//NewComp1->SetWorldLocation(FVector(TILE_SIZE *i, TILE_SIZE * j, 0.0f));
		NewComp1->SetupAttachment(MainChildCp);
		NewComp1->RegisterComponent();
		NewComp1->SetChildActorClass(ATargetsActor::StaticClass());

		// Choose a random starting location.
		int startI = roonsPos[i][0];
		int startY = roonsPos[i][1];

		for (int j = 0; j < roomWidth; ++j)
		{
			for (int z = 0; z < roomHeight; ++z)
			{
				int newI = startI + j;
				int newY = startY + z;
				// Check if the tile is valid.
				if (TileIsValid(newI, newY))
				{
					// Check if the tile is not on an outer wall.
					if ((newI != 0) && (newI != (GRID_WIDTH - 1)) && (newY != 0) &&
						(newY != (GRID_HEIGHT - 1)))
					{

						m_grid[newI][newY]->SetMesh(tiles[i]);
						m_grid[newI][newY]->SetScale(FVector(1.0f, 1.0f, 0.03f));

						m_grid[newI][newY]->SetPosition(FVector(m_grid[newI][newY]->GetActorLocation().X, m_grid[newI][newY]->GetActorLocation().Y, 0.0f));
						if (j == 1 && z == 1) {
							((ATargetsActor*)NewComp1->GetChildActor())->SetPosition(m_grid[newI][newY]->GetActorLocation());
							((ATargetsActor*)NewComp1->GetChildActor())->SetMesh(targets[i]);



						}

						if ((targets[i] == ETarget::TSTART) && (j == 0 && (z == 0)))
						{

							FActorSpawnParameters SpawnParams;
							SpawnParams.Owner = this;
							SpawnParams.Instigator = Instigator;

							// spawn the eyes of the ghost after death

							const FVector SpawnLocation = FVector(m_grid[newI][newY]->GetActorLocation().X, m_grid[newI][newY]->GetActorLocation().Y, 100.0f);
							const FRotator SpawnRotation = GetActorRotation();

							PlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>(Player->GetDefaultObject()->GetClass(), SpawnLocation, SpawnRotation, SpawnParams);

						}


					}
				}
			}
		}
	}
}






void AMazeGenerate::SetSize(int GWidth, int GHeight)
{
	
		GRID_WIDTH = GWidth;
		GRID_HEIGHT = GHeight;
	
}

