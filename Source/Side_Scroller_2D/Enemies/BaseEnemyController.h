// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyController.generated.h"


class ABasePlayer;
/**
 *
 */
UCLASS()
class SIDE_SCROLLER_2D_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseEnemyController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override; 

public:

	void MoveActor();


protected:

	TObjectPtr<ABasePlayer> PlayerReference;


};
