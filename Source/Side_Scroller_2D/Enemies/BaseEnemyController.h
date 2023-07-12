// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyController.generated.h"

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

public:
	virtual void Tick(float DeltaTime) override; 
	
	bool m_Flipmovement; 

protected:

	class ABaseEnemy* m_EnemyRef; 

	float m_Timer; 
	float m_Target; 

};
