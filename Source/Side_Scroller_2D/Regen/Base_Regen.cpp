// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Regen.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"



// Sets default values
ABase_Regen::ABase_Regen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = Collision;

	RegenParticles = CreateOptionalDefaultSubobject<UNiagaraComponent>(TEXT("RegenParticles"));
	RegenParticles->SetupAttachment(Collision);

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void ABase_Regen::BeginPlay()
{
	Super::BeginPlay();
	if(RegenParticles) // If the particle system exists, set the colors and intensity
	{
		RegenParticles->SetVariableLinearColor("FirstParticleColor", FirstParticleColor); 
		RegenParticles->SetVariableLinearColor("SecondParticleColor", SecondParticleColor);
		RegenParticles->SetFloatParameter("Intensity", ParticleIntensity);
	}

}

void ABase_Regen::RegenStats()
{
}

// Called every frame
void ABase_Regen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Collision->IsOverlappingActor(PlayerReference)) 
	{
		if (PlayerReference->GetMana() < PlayerReference->GetMaxMana()) // If the player's mana is less than the max mana, Reduce the particle Intensity
		{
			ParticleIntensity -= DeltaTime;
		}
	}
	if (ParticleIntensity <= 0)
	{
		Destroy(); // Destroy the regen object
	}


}

