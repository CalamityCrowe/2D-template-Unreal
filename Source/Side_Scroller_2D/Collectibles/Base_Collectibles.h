// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Collectibles.generated.h"

UENUM(BlueprintType)
enum class CollectType :uint8
{
	Health UMETA(DisplayName = "Health"),
	MaxHealth UMETA(DisplayName = "Max Health"),
	Mana UMETA(DisplayName = "Mana"),
	MaxMana UMETA(DisplayName = "Max Mana"),


};

UCLASS()
class SIDE_SCROLLER_2D_API ABase_Collectibles : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABase_Collectibles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(Category = "Sprite", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UPaperFlipbookComponent> m_Sprite;
	UPROPERTY(Category = "Collisions", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UCapsuleComponent> m_Collision;

protected:
	UPROPERTY(Category = "Collectible Type", EditDefaultsOnly, BluePrintReadOnly)
		TEnumAsByte<CollectType> m_CollectType; 

public:
	FORCEINLINE class UPaperFlipbookComponent* GetSprite() const { return m_Sprite; }

	UFUNCTION()
		virtual void CollectibleCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
