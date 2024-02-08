// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationComponent.h"
#include "EnemyAnimationComponent.generated.h"

class ABaseEnemy;
/**
 * 
 */
UCLASS()
class SIDE_SCROLLER_2D_API UEnemyAnimationComponent : public UAnimationComponent
{
	GENERATED_BODY()
	
public:
	UEnemyAnimationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ABaseEnemy> EnemyRef;

	virtual void HandleAnimation() override; 
};
