// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Collectibles.h"
#include "Restorative_Collectibles.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class CollectType :uint8
{
	Health UMETA(DisplayName = "Health"),
	MaxHealth UMETA(DisplayName = "Max Health"),
	Mana UMETA(DisplayName = "Mana"),
	MaxMana UMETA(DisplayName = "Max Mana"),


};

UCLASS()
class SIDE_SCROLLER_2D_API ARestorative_Collectibles : public ABase_Collectibles
{
	GENERATED_BODY()
public:
	ARestorative_Collectibles();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(Category = "Collectible Type", EditDefaultsOnly, BluePrintReadOnly)
		TEnumAsByte<CollectType> m_CollectType;

	UPROPERTY(Category = "Collectible Value", EditDefaultsOnly, BluePrintReadWrite)
		int m_CollectValue;

public:
	
		virtual void CollectibleCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override; 

};
