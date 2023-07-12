// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"

ABaseEnemyController::ABaseEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Flipmovement = false; 
	m_Target = 1.f; 
}

void ABaseEnemyController::BeginPlay()
{
	Super::BeginPlay(); 
	

	
}

void ABaseEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	
	m_Timer += DeltaTime;
	if (m_Timer >= m_Target) 
	{
		m_Timer = 0;
		m_Flipmovement = !m_Flipmovement; 
	}


}
