// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Sound_Actor.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
ABase_Sound_Actor::ABase_Sound_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = AudioComponent;

	RippleEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RippleEffect"));
	RippleEffect->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABase_Sound_Actor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABase_Sound_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

