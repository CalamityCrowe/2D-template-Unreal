// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Side_Scroller_2D/Projectiles/BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
ABasePlayer::ABasePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	m_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	m_SpringArmComponent->TargetArmLength = 300.f;
	m_SpringArmComponent->bEnableCameraLag = true;
	m_SpringArmComponent->CameraLagSpeed = 5.f;
	m_SpringArmComponent->SetRelativeRotation(FRotator(0, 0, 270));
	m_SpringArmComponent->bInheritPitch = false;
	m_SpringArmComponent->bInheritYaw = false;
	m_SpringArmComponent->bInheritRoll = false;

	m_SpringArmComponent->SetupAttachment(RootComponent);
	m_Camera->SetupAttachment(m_SpringArmComponent);

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	m_AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Collision"));
	m_AttackCollision->SetupAttachment(RootComponent);
	m_ProjectileSpawn = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile Spawn"));
	m_ProjectileSpawn->SetupAttachment(RootComponent);

	m_Footsteps_Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Footsteps Audio"));


	isSliding = false;
	isAttacking = false;


	m_MaxHealth = 100;
	m_Health = m_MaxHealth;
	m_newHealth = m_MaxHealth;
	m_MaxMana = 100;
	m_Mana = m_MaxMana;
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	SetupAnimationStates();
	m_AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasePlayer::AttackOverlap);
	m_AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_SocketLocation = m_SpringArmComponent->SocketOffset;

}

void ABasePlayer::UpdateAnimations()
{
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
}

void ABasePlayer::UpdateRotations()
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

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAnimations();
	if (m_isHurt == false)
	{
		UpdateRotations();
	}

	if (m_Health != m_newHealth)
	{
		AnimateHealthChange();
	}

	if (m_Health <= 0 && m_PlayDeath)
	{
		m_PlayDeath = false;
		GetSprite()->SetLooping(false);
	}



}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (InputComponent)
	{


		InputComponent->BindAction("Crouch", IE_Pressed, this, &ABasePlayer::CrouchInput);
		InputComponent->BindAction("Crouch", IE_Released, this, &ABasePlayer::UnCrouchInput);

		InputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
		InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

		InputComponent->BindAction("Fire", IE_Pressed, this, &ABasePlayer::FireProjectile);


		InputComponent->BindAction("Melee", IE_Pressed, this, &ABasePlayer::MeleeInput);
		InputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

	}


}

void ABasePlayer::SetupAnimationStates()
{
	if (GetSprite())
	{

		GetSprite()->OnFinishedPlaying.AddDynamic(this, &ABasePlayer::FinishedAnimation_Sliding);
		GetSprite()->OnFinishedPlaying.AddDynamic(this, &ABasePlayer::FinishedAnimation_Attacking);
		GetSprite()->OnFinishedPlaying.AddDynamic(this, &ABasePlayer::FinishedAnimation_Hurt);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Finished Adding Dynamics"));

	}
}

void ABasePlayer::MoveRight(float AxisInput)
{
	if (GetCharacterMovement()->IsCrouching() == false)
	{
		if (isAttacking == false && m_Health > 0 && m_isHurt == false)
		{
			AddMovementInput(FVector(1, 0, 0), AxisInput);
			if (GetCharacterMovement()->IsFalling() == false && GetCharacterMovement()->Velocity.SizeSquared() > 0 && m_Footsteps_Audio->IsPlaying() == false &&  isSliding == false)
			{
				m_Footsteps_Audio->Play();
			}
		}
	}
	else
	{
		if (abs(AxisInput) > 0)
		{
			UnCrouch();
			Sliding();
		}
	}

}

void ABasePlayer::CrouchInput()
{

	if (abs(GetCharacterMovement()->Velocity.X) > 0 && GetCharacterMovement()->IsFalling() == false)
	{
		Sliding();
	}
	else
	{
		Crouch();
	}

}

void ABasePlayer::UnCrouchInput()
{
	if (GetCharacterMovement()->IsCrouching())
	{
		UnCrouch();
	}
}

void ABasePlayer::LaunchPlayer(float X, float Vert)
{
	float x_Dir = (GetVelocity().X >= 0) ? 1 : -1;
	FVector direction = FVector(x_Dir * X, 0, Vert);
	LaunchCharacter(direction, false, false);

}

void ABasePlayer::Sliding()
{
	LaunchPlayer(1, 1);
	isSliding = true;
	GetSprite()->SetLooping(false);
}

void ABasePlayer::MeleeInput()
{
	if (isSliding)
	{
		LaunchPlayer(300, 300);
		isAttacking = true;
		GetSprite()->SetLooping(false);
		m_AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		PlayAttackSound(); 
	}
	else
	{
		switch (m_CurrentAttack)
		{
		case AttackStates::None:
			m_NextAttack = AttackStates::Attack1;
			break;
		case AttackStates::Attack1:
			m_NextAttack = AttackStates::Attack2;
			break;
		case AttackStates::Attack2:
			break;
		}
		isAttacking = true;
		GetSprite()->SetLooping(false);
		if (m_CurrentAttack == AttackStates::None)
		{
			m_CurrentAttack = m_NextAttack;
			m_NextAttack = AttackStates::None;
			m_AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			PlayAttackSound(); // calls the blueprints associated with this event 
		}
	}
	m_AttackCollision->Activate();
}


void ABasePlayer::FireProjectile()
{
	if (m_Mana && m_ProjectileSpawn)
	{
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = m_ProjectileSpawn->GetComponentLocation();
		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (ABaseProjectile* proj = GetWorld()->SpawnActor<ABaseProjectile>(m_Projectile, SpawnLocation, SpawnRotation, spawnParam))
		{
			m_Mana -= 10;
			proj = nullptr;
		}
	}
}

void ABasePlayer::PlayerHurt()
{
	m_HurtFlash = true;
	m_isHurt = true;
	GetSprite()->SetLooping(false);
	m_newHealth -= 10;

}

void ABasePlayer::Jump()
{
	ACharacter::Jump(); 
	if (GetCharacterMovement()->IsFalling() == false) 
	{
		UGameplayStatics::PlaySound2D(GetWorld(), m_JumpSound); 
	}
}

void ABasePlayer::FinishedAnimation_Attacking()
{

	if (isAttacking && isSliding)
	{
		isAttacking = false;
		isSliding = false;
		GetSprite()->SetLooping(true);
		GetSprite()->Play();
		m_AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
	else if (isAttacking)
	{

		switch (m_NextAttack)
		{
		case AttackStates::None:
			isAttacking = false;
			m_CurrentAttack = AttackStates::None;
			GetSprite()->SetLooping(true);
			GetSprite()->Play();
			m_AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		default:
			m_CurrentAttack = m_NextAttack;
			m_NextAttack = AttackStates::None;
			GetSprite()->Play();
			m_AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			m_AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			PlayAttackSound(); // calls the blueprints associated with this event
			break;

		}

	}


}
void ABasePlayer::FinishedAnimation_Sliding()
{
	if (isSliding && isAttacking == false)
	{
		isSliding = false;
		GetSprite()->SetLooping(true);
		GetSprite()->Play();
	}

}

void ABasePlayer::FinishedAnimation_Hurt()
{
	if (m_isHurt)
	{
		m_isHurt = false;
		m_HurtFlash = false;
		GetSprite()->SetLooping(true);
		GetSprite()->Play();
	}
}

void ABasePlayer::AttackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlapping"));

}



void ABasePlayer::AnimateHealthChange()
{
	m_Health = UKismetMathLibrary::Lerp(m_Health, m_newHealth, 0.1f);
	if (abs(m_Health - m_newHealth < 1.f))
	{
		m_Health = m_newHealth;
	}
}



