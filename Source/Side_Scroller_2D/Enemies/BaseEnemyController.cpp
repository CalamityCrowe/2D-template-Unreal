// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"
#include <Kismet/GameplayStatics.h>
#include <NavigationSystem.h>
#include "BaseEnemy.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"

ABaseEnemyController::ABaseEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ABaseEnemyController::BeginPlay()
{
	Super::BeginPlay();
	PlayerReference = Cast<ABasePlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


}

void ABaseEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABaseEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABaseEnemyController::MoveActor()
{
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	if (APawn* ControlledPawn = GetPawn())
	{
		const ANavigationData* NavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);

		if (ABaseEnemy* CurrentEnemy = Cast<ABaseEnemy>(ControlledPawn))
		{
			MoveToLocation(PlayerReference->GetActorLocation(), 10);

		}

	}
}

void ABaseEnemyController::StopActor()
{
	if (GetPawn()->GetVelocity().SquaredLength() > 0)
	{
		StopMovement();
	}
}
