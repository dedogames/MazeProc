// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MazeGameInstance.generated.h"

/**
 * Save value of Grid size on memory
 *
 */
UCLASS()
class MAZEPROGRAM_API UMazeGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Grid_Size;
};
