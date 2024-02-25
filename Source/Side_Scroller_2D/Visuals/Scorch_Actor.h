// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "Scorch_Actor.generated.h"

/**
 *
 */
UCLASS()
class SIDE_SCROLLER_2D_API AScorch_Actor : public ADecalActor
{
	GENERATED_BODY()

public:
	AScorch_Actor();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetDecalProperties(UMaterialInterface* DecalMaterial, FVector DecalSize);

private:
	float DecalLifeSpan = 5.0f;

	float Timer; 
};
