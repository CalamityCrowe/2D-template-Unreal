// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BaseEnemy.generated.h"

/**
 * This is a template that any of the enemies can inherit off of
 *
 * this will contain the basic knowledge to kill them along side a basic walk cycle
 *
 * this also contains functions that can handle the updating of animations and rotating the enemy based on their movement direction
 */

class UEnemyAnimationComponent; 
class ABaseEnemyController;

UENUM(BlueprintType)
enum class EnemyState :uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Hurt UMETA(DisplayName = "Hurt"),
	Walk UMETA(DisplayName = "Walk"),
	Attack UMETA(DisplayName = "Attack"),
	Dead UMETA(DisplayName = "Dead")

};
UCLASS()
class SIDE_SCROLLER_2D_API ABaseEnemy : public APaperCharacter
{
	GENERATED_BODY()

public:

	ABaseEnemy();

protected:
	virtual void BeginPlay() override;

	virtual void HandleEnemyMovement();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	virtual void Tick(float DeltaTime) override;
	void UpdateRotation();

protected:


	UPROPERTY(EditDefaultsOnly,Category = "Animations", meta =(AllowPrivateAccess = true))
	TObjectPtr<UEnemyAnimationComponent> EnemyAnimationComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
		bool isDead;




	TObjectPtr<ABaseEnemyController> EnemyController;

};
