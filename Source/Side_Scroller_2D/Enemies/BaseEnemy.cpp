// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseEnemyController.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"
#include "Components/CapsuleComponent.h"
#include "Side_Scroller_2D/Component/EnemyAnimationComponent.h"
#include "Perception/PawnSensingComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	EnemyAnimationComponent = CreateDefaultSubobject<UEnemyAnimationComponent>(TEXT("EnemyAnimationComponent"));
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ABaseEnemy::OnSeePawn);
	bCanSeePlayer = false;	
	CurrentState = EEnemyState::Idle;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	//m_EnemyController = Cast<ABaseEnemyController>(GetController());
	if ((EnemyController = Cast<ABaseEnemyController>(GetController())))
	{
		GEngine->AddOnScreenDebugMessage(74, 2, FColor::Cyan, TEXT("Enemy Ref Set"));
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnOverlapBegin);
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentState  == EEnemyState::Walk)
	{
		if (EnemyController) 
		{
			EnemyController->MoveActor();
		}
		if (bCanSeePlayer) 
		{
			if()
		}
	}
	else
	{
		isDead = true;
	}
	UpdateRotation();

}


void ABaseEnemy::UpdateRotation()
{


	if (IsValid(GetController())) // checks if the controller is valid
	{
		if (GetVelocity().X > 0) // checks if velocity is greater than 0
		{
			SetActorRotation(FRotator(0, 0, 0)); // sets the rotation to 0 
		}
		if (GetVelocity().X < 0) // checks if the velocity is less than 0 
		{
			SetActorRotation(FRotator(0, 180, 0)); // sets the actors rotation to 180 in the yaw 
		}
	}

}

void ABaseEnemy::OnSeePawn(APawn* Pawn)
{
	if (ABasePlayer* tempPlayer = Cast<ABasePlayer>(Pawn))
	{
		CurrentState = EEnemyState::Walk;
		bCanSeePlayer = true;
	}
}


void ABaseEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && IsValid(OtherActor) && isDead == false) // checks if the other actor is not itself and is valid, along with checking if itself is dead
	{
		if (ABasePlayer* tempPlayer = Cast<ABasePlayer>(OtherActor))
		{
			if (tempPlayer->IsHurt() == false)
			{
				tempPlayer->PlayerHurt(); // calls the function to hurt the player
				float X_Force = (tempPlayer->GetActorLocation().X - GetActorLocation().X > 0) ? 1 : -1; // checks which direction it should launch the player


				FVector dir = FVector((X_Force) * 250, 0, 200);

				tempPlayer->LaunchCharacter(dir, false, false);

				tempPlayer->PlayHitSound(); 
			}

		}
	}
}
