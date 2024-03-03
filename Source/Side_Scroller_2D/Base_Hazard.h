// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Hazard.generated.h"

UCLASS()
class SIDE_SCROLLER_2D_API ABase_Hazard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABase_Hazard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
