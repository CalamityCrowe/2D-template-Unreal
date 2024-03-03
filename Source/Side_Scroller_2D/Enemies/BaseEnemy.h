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
class UPawnSensingComponent; 

UENUM(BlueprintType)
enum class EEnemyState :uint8
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


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private :
	virtual void Tick(float DeltaTime) override;
	void UpdateRotation();

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = true))
	TObjectPtr<UEnemyAnimationComponent> EnemyAnimationComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	bool isDead;

	EEnemyState CurrentState;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPawnSensingComponent> PawnSensingComponent;

	bool bCanSeePlayer; 


public:

	EEnemyState GetCurrentState() const { return CurrentState; }

	TObjectPtr<ABaseEnemyController> EnemyController;

};
