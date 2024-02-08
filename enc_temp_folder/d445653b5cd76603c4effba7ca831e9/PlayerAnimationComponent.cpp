// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimationComponent.h"

#include "Side_Scroller_2D/Player/BasePlayer.h"

UPlayerAnimationComponent::UPlayerAnimationComponent()
{
}



void UPlayerAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	if(PlayerRef = Cast<ABasePlayer>(GetOwner()))
	{
		GEngine->AddOnScreenDebugMessage(74, 2, FColor::Cyan, TEXT("Player Ref Set")); 
	}
}

void UPlayerAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerAnimationComponent::HandleAnimation()
{
	if(PlayerRef != nullptr)
	{
		// setup required before it can be done

		/*
				const FVector PlayerVelocity = GetVelocity();
				const float PlayerSpeedSqr = PlayerVelocity.SizeSquared(); // gets the length of the velocity squared

				UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? m_RunAnimation : m_IdleAnimation;
				DesiredAnimation = (abs(PlayerVelocity.Z) > 0.0f) ? m_JumpAnimation : DesiredAnimation;
				DesiredAnimation = (GetCharacterMovement()->IsCrouching()) ? m_CrouchAnimation : DesiredAnimation;
				DesiredAnimation = (isSliding) ? m_SlideAnimation : DesiredAnimation;
				DesiredAnimation = (isAttacking && isSliding) ? m_AttackAnimationSlide : DesiredAnimation;
				DesiredAnimation = (isAttacking && m_CurrentAttack == AttackStates::Attack1) ? m_AttackAnimation1 : DesiredAnimation;
				DesiredAnimation = (isAttacking && m_CurrentAttack == AttackStates::Attack2) ? m_AttackAnimation2 : DesiredAnimation;
				DesiredAnimation = (m_isHurt) ? m_HurtAnimation : DesiredAnimation;
				DesiredAnimation = (m_Health <= 0) ? m_DeathAnimation : DesiredAnimation;


				if (GetSprite()->GetFlipbook() != DesiredAnimation)
				{
					GetSprite()->SetFlipbook(DesiredAnimation);
				}
		 
		 */
	}
}