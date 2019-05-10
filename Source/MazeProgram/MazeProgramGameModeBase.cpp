// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeProgramGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"

AMazeProgramGameModeBase::AMazeProgramGameModeBase()
{ 

 
}

void AMazeProgramGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	/* Destroy player loaded automatically*/
	UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->Destroy();
}
