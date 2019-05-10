// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetsActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATargetsActor::ATargetsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	 

	BoxTriggerCP = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	  RootComponent = BoxTriggerCP;

	Sprite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCp"));
	Sprite->SetupAttachment(BoxTriggerCP);

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>FinishTargetObj(TEXT("StaticMesh'/Game/Finish/SM_Finish.SM_Finish'"));
	if (FinishTargetObj.Succeeded())
	{
		Targets.Add(ETarget::TFINISH, FinishTargetObj.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>StartTargetObj(TEXT("StaticMesh'/Game/Start/SM_Start.SM_Start'"));
	if (StartTargetObj.Succeeded())
	{
		Targets.Add(ETarget::TSTART, StartTargetObj.Object);
	}

	
 

}


void ATargetsActor::SetPosition(FVector Pos )
{
	LocationTile = Pos;
	Sprite->SetWorldLocation(Pos);
	 
}

void ATargetsActor::SetMesh(ETarget Tex)
{
	TypeTile = Tex;

	UStaticMesh *m = Targets.FindRef(Tex);
	if (m)
		Sprite->SetStaticMesh(m);
}

// Called when the game starts or when spawned
void ATargetsActor::BeginPlay()
{
	Super::BeginPlay();
	
}
 

