// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"

ABaseEnemyController::ABaseEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;



}

void ABaseEnemyController::BeginPlay()
{
	Super::BeginPlay(); 
	

	
}

void ABaseEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	
	MoveToLocation(FVector(0,0,-446), 10.f); 
}
