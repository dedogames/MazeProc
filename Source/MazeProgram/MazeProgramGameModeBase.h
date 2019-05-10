/*

	Project: Name of Project
	Developer: Gelson G. Rodrigues
	Date: 05-10-2019

	***************
	* Description *
	***************
	 

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
#include "GameFramework/GameModeBase.h"
#include "MazeProgramGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAZEPROGRAM_API AMazeProgramGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMazeProgramGameModeBase();
 
	virtual void BeginPlay() override;
	
};
