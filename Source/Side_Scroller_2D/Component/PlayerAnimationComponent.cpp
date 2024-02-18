// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimationComponent.h"

#include "PaperFlipbookComponent.h"
#include "U2D_AnimationContainer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"

UPlayerAnimationComponent::UPlayerAnimationComponent()
{
}



void UPlayerAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	if ((PlayerRef = Cast<ABasePlayer>(GetOwner())))
	{
		GEngine->AddOnScreenDebugMessage(74, 2, FColor::Cyan, TEXT("Player Ref Set"));
	}
}

void UPlayerAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HandleAnimation();
}

void UPlayerAnimationComponent::HandleAnimation()
{
	if (PlayerRef != nullptr)
	{

		// setup required before it can be done

		const FVector PlayerVelocity = PlayerRef->GetVelocity();
		const float PlayerSpeedSqr = PlayerVelocity.SizeSquared(); // gets the length of the velocity squared

		UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? CurrentAnimationsData->Movement_Animations[0] : CurrentAnimationsData->Miscellaneous_Animations[0];
		DesiredAnimation = (abs(PlayerVelocity.Z) > 0.0f) ? CurrentAnimationsData->Movement_Animations[1] : DesiredAnimation;
		DesiredAnimation = (PlayerRef->GetCharacterMovement()->IsCrouching()) ? CurrentAnimationsData->Miscellaneous_Animations[1] : DesiredAnimation;
		DesiredAnimation = (PlayerRef->IsSliding()) ? CurrentAnimationsData->Movement_Animations[2] : DesiredAnimation;
		DesiredAnimation = (PlayerRef->IsAttacking() && PlayerRef->IsSliding()) ? CurrentAnimationsData->Attack_Animations[0] : DesiredAnimation;
		DesiredAnimation = (PlayerRef->IsAttacking() && PlayerRef->GetCurrentAttack() == EAttackStates::Attack1) ? CurrentAnimationsData->Attack_Animations[1] : DesiredAnimation;
		DesiredAnimation = (PlayerRef->IsAttacking() && PlayerRef->GetCurrentAttack() == EAttackStates::Attack2) ? CurrentAnimationsData->Attack_Animations[2] : DesiredAnimation;
		DesiredAnimation = (PlayerRef->IsHurt()) ? CurrentAnimationsData->Miscellaneous_Animations[2] : DesiredAnimation;
		DesiredAnimation = (PlayerRef->GetHealth() <= 0) ? CurrentAnimationsData->Miscellaneous_Animations[3] : DesiredAnimation;


		if (PlayerRef->GetSprite()->GetFlipbook() != DesiredAnimation)
		{
			PlayerRef->GetSprite()->SetFlipbook(DesiredAnimation);
		}
	}
}