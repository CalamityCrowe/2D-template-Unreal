// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true; 

	m_Health = 100.f;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAnimation();
	UpdateRotation();

	
}

void ABaseEnemy::UpdateAnimation()
{
	const FVector EnemyVelocity = GetVelocity();
	const float EnemySpeedSqr = EnemyVelocity.SizeSquared(); // gets the length of the velocity squared

	UPaperFlipbook* DesiredAnimation = (EnemySpeedSqr > 0.0f) ? m_RunAnimation : m_IdleAnimation;
	DesiredAnimation = (m_Health <= 0.f) ? m_DeathAnimation : DesiredAnimation;


	
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}


}

void ABaseEnemy::UpdateRotation()
{
	if (IsValid(GetController()))
	{
		if (GetVelocity().X > 0)
		{
			GetController()->SetControlRotation(FRotator(0, 0, 0));
		}
		if (GetVelocity().X < 0)
		{
			GetController()->SetControlRotation(FRotator(0, 180, 0));
		}
	}
}
