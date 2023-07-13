// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseEnemyController.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"
#include "Components/CapsuleComponent.h"

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
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnOverlapBegin);
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_isDead == false)
	{
		HandleEnemyMovement();
	}
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

void ABaseEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && IsValid(OtherActor) && m_isDead == false) // checks if the other actor is not itself and is valid, along with checking if itself is dead
	{
		if (ABasePlayer* tempPlayer = Cast<ABasePlayer>(OtherActor))
		{
			if (tempPlayer->isHurt() == false)
			{
				tempPlayer->PlayerHurt(); // calls the function to hurt the player
				float X_Force = (tempPlayer->GetActorLocation().X - GetActorLocation().X > 0) ? 1 : -1; // checks which direction it should launch the player
				//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Impact X: %f"), SweepResult.ImpactNormal.X));


				FVector dir = FVector((X_Force) * 250, 0, 200);

				tempPlayer->LaunchCharacter(dir, false, false);

				//tempPlayer->GetCharacterMovement()->Velocity = FVector();			
			}

		}
	}
}
