// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Side_Scroller_2D/Projectiles/BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


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

	m_ProjectileSpawn = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	m_ProjectileSpawn->SetupAttachment(RootComponent);

	isSliding = false;
	isAttacking = false;


	m_Health = 10;
	m_Mana = 100; 
	m_MaxHealth = 100;
	m_MaxMana = 100;
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	SetupAnimationStates();


}

void ABasePlayer::UpdateAnimations()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared(); // gets the length of the velocity squared

	UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? m_RunAnimation : m_IdleAnimation;
	DesiredAnimation = (abs(PlayerVelocity.Z) > 0.0f) ? m_JumpAnimation : DesiredAnimation;
	DesiredAnimation = (GetCharacterMovement()->IsCrouching()) ? m_CrouchAnimation : DesiredAnimation;
	DesiredAnimation = (isSliding) ? m_SlideAnimation : DesiredAnimation;
	DesiredAnimation = (isAttacking) ? m_AttackAnimationSlide : DesiredAnimation;

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
	UpdateRotations();

}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (InputComponent)
	{


		InputComponent->BindAction("Crouch", IE_Pressed, this, &ABasePlayer::CrouchInput);
		InputComponent->BindAction("Crouch", IE_Released, this, &ABasePlayer::UnCrouchInput);

		InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
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
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Finished Adding Dynamics"));

	}
}

void ABasePlayer::MoveRight(float AxisInput)
{
	if (GetCharacterMovement()->IsCrouching() == false)
	{
		if (isAttacking == false)
		{
			AddMovementInput(FVector(1, 0, 0), AxisInput);
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
	}
}

void ABasePlayer::FireProjectile()
{
	if (m_Mana)
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Sliding"));
}

void ABasePlayer::FinishedAnimation_Attacking()
{

	if (isAttacking)
	{
		isAttacking = false;
		isSliding = false;
		GetSprite()->SetLooping(true);
		GetSprite()->Play();
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



