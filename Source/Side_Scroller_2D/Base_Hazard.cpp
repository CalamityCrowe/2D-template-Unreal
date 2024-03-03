// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Hazard.h"
#include "PaperFlipbookComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABase_Hazard::ABase_Hazard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void ABase_Hazard::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ABase_Hazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


