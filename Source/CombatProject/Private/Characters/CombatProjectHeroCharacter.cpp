// Spirit Revenge All Rights Reserved


#include "Characters/CombatProjectHeroCharacter.h"
#include "CombatProjectDebugHelper.h"
#include "CombatProjectGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Input/CombatProjectInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACombatProjectHeroCharacter::ACombatProjectHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void ACombatProjectHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assgin a valid data asset as input config"));
	
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UCombatProjectInputComponent* CombatProjectInputComponent = CastChecked<UCombatProjectInputComponent>(PlayerInputComponent);
	
	CombatProjectInputComponent->BindNativeInputAction(InputConfigDataAsset, CombatProjectGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	CombatProjectInputComponent->BindNativeInputAction(InputConfigDataAsset, CombatProjectGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
}

void ACombatProjectHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	Debug::Print(TEXT("CombatProjectHeroCharacter"));
}

void ACombatProjectHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);
	
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotator.RotateVector(FVector::ForwardVector);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotator.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACombatProjectHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
