// Spirit Revenge All Rights Reserved


#include "AnimInstances/CombatProjCharacterAnimInstance.h"

#include "Characters/CombatProjectBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCombatProjCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ACombatProjectBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UCombatProjCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.f;
}
