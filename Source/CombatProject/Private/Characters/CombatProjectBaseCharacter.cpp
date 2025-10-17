// Spirit Revenge All Rights Reserved


#include "Characters/CombatProjectBaseCharacter.h"

// Sets default values
ACombatProjectBaseCharacter::ACombatProjectBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
}


