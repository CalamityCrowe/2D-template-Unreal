// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class SIDE_SCROLLER_2D_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Movement")
		class UProjectileMovementComponent* m_ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Sprite")
		class UPaperFlipbookComponent* m_ProjectileSprite;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Collision")
		class USphereComponent* m_Collision;

};
