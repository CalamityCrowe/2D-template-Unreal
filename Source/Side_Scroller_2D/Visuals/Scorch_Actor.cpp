// Fill out your copyright notice in the Description page of Project Settings.


#include "Scorch_Actor.h"

AScorch_Actor::AScorch_Actor()
{
	PrimaryActorTick.bCanEverTick = true;
	DecalLifeSpan = 2.0f;
}

void AScorch_Actor::BeginPlay()
{
	Super::BeginPlay();
}

void AScorch_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;
	if (Timer > DecalLifeSpan)
	{
		Destroy();
	}
}

void AScorch_Actor::SetDecalProperties(UMaterialInterface* DecalMaterial, FVector DecalSize)
{
	SetDecalMaterial(DecalMaterial);
}
