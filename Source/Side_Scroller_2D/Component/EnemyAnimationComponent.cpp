// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimationComponent.h"

#include "Side_Scroller_2D/Enemies/BaseEnemy.h"

UEnemyAnimationComponent::UEnemyAnimationComponent()
{
}

void UEnemyAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	if((EnemyRef = Cast<ABaseEnemy>(GetOwner())))
	{
		GEngine->AddOnScreenDebugMessage(74, 2, FColor::Cyan, TEXT("Enemy Ref Set"));

	}
}

void UEnemyAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HandleAnimation(); 
}

void UEnemyAnimationComponent::HandleAnimation()
{
	if(EnemyRef!= nullptr)
	{

	}
}
