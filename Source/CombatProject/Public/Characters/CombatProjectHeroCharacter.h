// Spirit Revenge All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/CombatProjectBaseCharacter.h"
#include "CombatProjectHeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class COMBATPROJECT_API ACombatProjectHeroCharacter : public ACombatProjectBaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
