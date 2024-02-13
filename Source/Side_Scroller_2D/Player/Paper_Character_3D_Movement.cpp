// Fill out your copyright notice in the Description page of Project Settings.


#include "Paper_Character_3D_Movement.h"

#include "EnhancedInputSubsystems.h"

APaper_Character_3D_Movement::APaper_Character_3D_Movement()
{
}

void APaper_Character_3D_Movement::BeginPlay()
{
	Super::BeginPlay();
}

void APaper_Character_3D_Movement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APaper_Character_3D_Movement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PC = Cast<APlayerController>(GetController())) // tries to grab an instance of the player controller
	{
		if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer()) // gets the local player from the controller
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())  // gets the enhanced input from the local input system
			{
				InputSystem->ClearAllMappings(); // clears any mapping contexts if they had been assigned by mistake
				InputSystem->AddMappingContext(InputMappingContext, 0); // assigns the mapping contexts as the highest priority
			}
		}
	}

	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent)) // attempts to cast to the enhanced input system
	{
		if (InputData)
		{
			PEI->BindAction(InputData->IA_Movement, ETriggerEvent::Triggered, this, &ABasePlayer::MovePlayer);
			PEI->BindAction(InputData->IA_Jump, ETriggerEvent::Started, this, &ABasePlayer::Jump);
			PEI->BindAction(InputData->IA_Crouch, ETriggerEvent::Started, this, &ABasePlayer::CrouchInput);
			PEI->BindAction(InputData->IA_Crouch, ETriggerEvent::Completed, this, &ABasePlayer::UnCrouchInput);
			PEI->BindAction(InputData->IA_Attack, ETriggerEvent::Started, this, &ABasePlayer::MeleeInput);

		}

	}
}

void APaper_Character_3D_Movement::MovePlayer(const FInputActionValue& val)

{

}
