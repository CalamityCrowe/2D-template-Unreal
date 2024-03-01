// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UPaperFlipbookComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

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
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Movement", meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> m_ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Sprite", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPaperFlipbookComponent> m_ProjectileSprite;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Collision", meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> m_Collision;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraComponent> TrailEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> ImpactReference;


};
