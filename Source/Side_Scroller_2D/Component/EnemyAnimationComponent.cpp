// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimationComponent.h"

#include "PaperFlipbookComponent.h"
#include "U2D_AnimationContainer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Side_Scroller_2D/Enemies/BaseEnemy.h"

UEnemyAnimationComponent::UEnemyAnimationComponent()
{
}

void UEnemyAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	if ((EnemyRef = Cast<ABaseEnemy>(GetOwner())))
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
	if (EnemyRef != nullptr)
	{
		const FVector EnemyVelocity = EnemyRef->GetVelocity();
		const float EnemySpeedSqr = EnemyVelocity.SizeSquared(); // gets the length of the velocity squared

		UPaperFlipbook* DesiredAnimation = (EnemySpeedSqr > 0.0f) ? CurrentAnimationsData->Movement_Animations[0] : CurrentAnimationsData->Miscellaneous_Animations[0];

		if (EnemyRef->GetSprite()->GetFlipbook() != DesiredAnimation)
		{
			EnemyRef->GetSprite()->SetFlipbook(DesiredAnimation);
		}
	}
}
