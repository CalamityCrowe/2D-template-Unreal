// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttachment.h"

#include "EnhancedInputComponent.h"
#include "Components/ArrowComponent.h"
#include "Side_Scroller_2D/Inputs/InputConfigData.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"
#include "Side_Scroller_2D/Projectiles/BaseProjectile.h"

// Sets default values for this component's properties
UWeaponAttachment::UWeaponAttachment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponAttachment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	 

}

void UWeaponAttachment::SetupInput(ABasePlayer* PR)
{
	if (PR == nullptr)
	{
		return;
	}
	if (APlayerController* PC = Cast<APlayerController>(PR->GetController()))
	{
		if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PC->InputComponent))
		{
			PEI->BindAction(PR->GetInputData()->IA_FireProjectile, ETriggerEvent::Started, this, &UWeaponAttachment::SpawnProjectile);
		}
	}

	PlayerRef = PR;
}

void UWeaponAttachment::SpawnProjectile()
{
	if (ProjectileRef)
	{
		if (PlayerRef->GetMana())
		{
			const FVector SpawnLocation = GetComponentLocation();
			const FRotator SpawnRotation = GetComponentRotation();
			const FActorSpawnParameters SpawnParams;
			if (ABaseProjectile* TempProjectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileRef, SpawnLocation, SpawnRotation, SpawnParams))
			{
				PlayerRef->ReduceMana(10); // this needs changed so it uses the projectile cost
			}

		}
	}
}


// Called every frame
void UWeaponAttachment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
