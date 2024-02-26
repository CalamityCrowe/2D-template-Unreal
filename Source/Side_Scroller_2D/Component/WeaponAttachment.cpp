// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttachment.h"
#include "WeaponAttachment.h"

#include "EnhancedInputComponent.h"
#include "Components/ArrowComponent.h"
#include "Side_Scroller_2D/Inputs/InputConfigData.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"
#include "Side_Scroller_2D/Projectiles/BaseProjectile.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Side_Scroller_2D/Visuals/Scorch_Actor.h"

// Sets default values for this component's properties
UWeaponAttachment::UWeaponAttachment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentMagic = EMagicType::Laser; // sets the default value to missile

	BeamEffect = CreateOptionalDefaultSubobject<UNiagaraComponent>("Beam Effect"); // creates the beam effect component

	bBeamActive = false; // sets the beam to be inactive by default
	RelativeBeamYaw = 0.0f; // sets the relative yaw to 0.0f
	BeamSpeed = 90.0f; // sets the speed of the beam to 90.0f
	// ...
}


// Called when the game starts
void UWeaponAttachment::BeginPlay()
{
	Super::BeginPlay();

	// ...


}

///<summary> Setup Input function
///
///<para> This is how you would go about binding a function to the players input from within a component that gets attached to the player without
///		  creating a function in the player to call the spawn logic from within here	
///
///		  this has been made virtual in case an additional layer of inheritance needs to be made for a new mapping context to be added for the relevant inputs to be used correctly
///
///</summary>


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
			PEI->BindAction(PR->GetInputData()->IA_FireProjectile, ETriggerEvent::Started, this, &UWeaponAttachment::CastMagic);
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
				PlayerRef->ReduceMana(ProjectileCosts[0]); // this needs changed so it uses the projectile cost
			}

		}
	}
}

void UWeaponAttachment::CastMagic()
{
	switch (CurrentMagic)
	{
	case EMagicType::Missile:
		SpawnProjectile(); // this spawns the magic projectile
		break;
	case EMagicType::Laser:
		FireBeam(); // this fires the magic beam
		break;
	default:
		break;
	}
}

void UWeaponAttachment::FireBeam()
{
	if (BeamEffect && bBeamActive == false)
	{
		bBeamActive = true; // this sets the beam to be active
		BeamEffect->Activate(); // this activates the beam effect
		PlayerRef->ReduceMana(ProjectileCosts[1]); // this reduces the mana of the player
	}

}

bool UWeaponAttachment::LineTraceMethod(FVector StartPos, FVector EndPos, FHitResult& HitResult)
{
	FCollisionQueryParams Query;
	Query.AddIgnoredActor(PlayerRef); // this ignores the player
	FCollisionResponseParams Response; 
	return GetWorld()->LineTraceSingleByChannel(HitResult, StartPos, EndPos, ECollisionChannel::ECC_Visibility, Query,Response);
}


// Called every frame
void UWeaponAttachment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bBeamActive)
	{
		RelativeBeamYaw += DeltaTime * BeamSpeed; // this is the speed at which the beam rotates
		BeamEffect->SetRelativeRotation(FRotator(0, RelativeBeamYaw, 0)); // this sets the rotation of the beam
		FVector StartPos = PlayerRef->GetActorLocation() + FVector(0, 0, 30); // this gets the start position of the beam
		FVector EndPos = (PlayerRef->GetActorLocation() - FVector(0,0,100)) + (BeamEffect->GetForwardVector() * 200); // this gets the end position of the beam
		FHitResult HitResult; // this is the hit result of the beam
	//	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Green, false, 0.5, 0, 0.5);

		if (BeamEffect->IsActive() == false) { BeamEffect->Activate(true); }
		FName BeamEnd = TEXT("BeamEnd"); // this is the name of the parameter in the beam effect
		BeamEffect->SetWorldLocation(StartPos);
		BeamEffect->SetVectorParameter(BeamEnd, EndPos);
		BeamEffect->SetVariableLinearColor(TEXT("ParticleColour"), FLinearColor(1, 0, 0, 1));


		if (LineTraceMethod(StartPos, EndPos, HitResult)) // this checks if the beam has hit anything
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			if(UNiagaraComponent* tempComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ImpactReference,HitResult.ImpactPoint))
			{
				tempComponent->SetVariableLinearColor(TEXT("ParticleColour"), FLinearColor(1, 0, 0, 1));
			}
			if(AScorch_Actor* tempScorch = GetWorld()->SpawnActor<AScorch_Actor>(ScorchRef,HitResult.ImpactPoint,FRotator(),SpawnParams))
			{
				// do additional setups for the decal
			}
			// do something to damage the enemy
		}
		if (RelativeBeamYaw > 360.0f)
		{
			RelativeBeamYaw = 0.0f;
			bBeamActive = false;
			BeamEffect->Deactivate();
		}
	}
	else
	{

	}

}

