// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Collectibles.h"
#include "PowerUp_Collectibles.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum class PowerUpType :uint8
{
	Speed UMETA(DisplayName = "Speed"),
	Strength UMETA(DisplayName = "Strength"),
};

UCLASS()
class SIDE_SCROLLER_2D_API APowerUp_Collectibles : public ABase_Collectibles
{
	GENERATED_BODY()
public:
	APowerUp_Collectibles();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
protected:

	UPROPERTY(Category = "Power Up Type", EditDefaultsOnly, BlueprintReadOnly)
		PowerUpType m_PowerUpType;

public:
	virtual void CollectibleCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
