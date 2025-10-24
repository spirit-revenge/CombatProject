// Spirit Revenge All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/CombatProjectBaseAnimInstance.h"
#include "CombatProjCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class ACombatProjectBaseCharacter;
/**
 * 
 */
UCLASS()
class COMBATPROJECT_API UCombatProjCharacterAnimInstance : public UCombatProjectBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	ACombatProjectBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};
