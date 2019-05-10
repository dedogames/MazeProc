// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeItem.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "MazeGenerate.h"

 

AMazeItem::AMazeItem()
{
	BoxCp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCp"));

	Sprite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCp"));
	RootComponent = BoxCp;
	Sprite->SetupAttachment(BoxCp);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockObj(TEXT("StaticMesh'/Game/Maze/SM_Maze.SM_Maze'"));
	if (BlockObj.Succeeded())
	{
		Tiles.Add(ETile::WALL, BlockObj.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FloorObj(TEXT("StaticMesh'/Game/Maze/Floor.Floor'"));
	if (FloorObj.Succeeded())
	{
		Tiles.Add(ETile::FLOOR, FloorObj.Object);
	}


	

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FinishObj(TEXT("StaticMesh'/Game/Maze/Finish.Finish'"));
	if (FinishObj.Succeeded())
	{
		Tiles.Add(ETile::FINISH,FinishObj.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>StartObj(TEXT("StaticMesh'/Game/Maze/sTART.start'"));
	if (StartObj.Succeeded())
	{
		Tiles.Add(ETile::START, StartObj.Object);
	}
	
	
	 
	
}

/*
	Restart Game is implemented on BP_MazeGrid
*/

void AMazeItem::OnOverlapCP(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	 
	
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) && TypeTile == ETile::FINISH)
	{ 
		TArray<AActor*> MazeGrid;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMazeGenerate::StaticClass(), MazeGrid);
		((AMazeGenerate*)  MazeGrid[0])->RestartGame();
	}
}

/*
	Set position on Scene and on Grid
*/
void AMazeItem::SetPosition(FVector Pos,int C, int R)
{
	LocationTile = Pos;
	Sprite->SetWorldLocation(Pos);
	if (C >= 0)
	{
		columnIndex = C;
		rowIndex = R;
	}
}

FVector AMazeItem::GetActorLocation()
{
	return Sprite->GetComponentLocation();
}

void AMazeItem::SetMesh(ETile Tex)
{ 
	TypeTile = Tex;
	
	UStaticMesh *m = Tiles.FindRef(Tex);
	if(m)
		Sprite->SetStaticMesh(m);

	/*
		After set mesh , enable overlap only on SM_FINISH
	*/
	if (Tex == ETile::FINISH)
	{
		Sprite->SetCollisionObjectType(ECC_WorldDynamic); 
		Sprite->SetCollisionResponseToAllChannels(ECR_Overlap);
		Sprite->GetGenerateOverlapEvents();
		Sprite->OnComponentBeginOverlap.AddDynamic(this, &AMazeItem::OnOverlapCP);
	}
}

void AMazeItem::SetScale(FVector Scale)
{
	Sprite->SetWorldScale3D(Scale);
}

void AMazeItem::BeginPlay()
{
	Super::BeginPlay();
 
	
}
