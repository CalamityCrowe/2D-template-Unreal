// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseEnemyController.h"


ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	m_Health = 100.f;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	//m_EnemyController = Cast<ABaseEnemyController>(GetController());
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleEnemyMovement();
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
			SetActorRotation(FRotator(0, 0, 0));
			GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Red, FString::Printf(TEXT("Rotation: %f"), GetActorRotation().Yaw));
		}
		if (GetVelocity().X < 0)
		{
			SetActorRotation(FRotator(0, 180, 0));
			GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Rotation: %f"), GetActorRotation().Yaw));
		}
	}

}

void ABaseEnemy::HandleEnemyMovement()
{
	//if (IsValid(GetController()))
	//{
	//	if (GetControlRotation().Yaw > 0)
	//	{
	//		AddMovementInput(FVector(1, 0, 0), -1);
	//	}
	//	else
	//	{
	//		AddMovementInput(FVector(1, 0, 0), 1);

	//	}
	//}

	if (IsValid(GetController()))
	{
		if (ABaseEnemyController* temp = Cast<ABaseEnemyController>(GetController()))
		{
			if (temp->m_Flipmovement == true)
			{
				AddMovementInput(FVector(1, 0, 0), 1);
			}
			else
			{
				AddMovementInput(FVector(1, 0, 0), -1);
			}
		}
	}
}
