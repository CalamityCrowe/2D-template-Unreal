// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationComponent.h"
#include "PlayerAnimationComponent.generated.h"

class ABasePlayer;
/**
 * 
 */
UCLASS()
class SIDE_SCROLLER_2D_API UPlayerAnimationComponent : public UAnimationComponent
{
	GENERATED_BODY()
public:
	UPlayerAnimationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ABasePlayer> PlayerRef; 

	void HandleAnimation(); 


};
