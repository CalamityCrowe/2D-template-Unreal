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
#include "Side_Scroller_2D/Component/PlayerAnimationComponent.h"


// Sets default values
ABasePlayer::ABasePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 5.f;
	SpringArmComponent->SetRelativeRotation(FRotator(0, 0, 270));
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;

	SpringArmComponent->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	PlayerAnimationComponent = CreateOptionalDefaultSubobject<UPlayerAnimationComponent>(TEXT("Animation Component"));


	AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Collision"));
	AttackCollision->SetupAttachment(RootComponent);
	ProjectileSpawn = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawn->SetupAttachment(RootComponent);

	Footsteps_Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Footsteps Audio"));


	isSliding = false;
	isAttacking = false;


	MaxHealth = 100;
	Health = MaxHealth;
	newHealth = MaxHealth;
	MaxMana = 100;
	Mana = MaxMana;
	newMana = MaxMana;
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	SetupAnimationStates();
	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasePlayer::AttackOverlap);
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SocketLocation = SpringArmComponent->SocketOffset;

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
	
	if (bHurt == false)
	{
		UpdateRotations();
	}

	if (Health != newHealth)
	{
		AnimateHealthChange();
	}
	if (Mana != newMana)
	{
		AnimateManaChange();
	}



	if (Health <= 0 && PlayDeath)
	{
		PlayDeath = false;
		GetSprite()->SetLooping(false);
	}



}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (InputComponent)
	{
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
		AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		PlayAttackSound();
	}
	else
	{
		if (GetCharacterMovement()->Velocity.Y != 0)
		{
			switch (CurrentAttack)
			{
			case AttackStates::None:
				NextAttack = AttackStates::Attack1;
				break;
			case AttackStates::Attack1:
				NextAttack = AttackStates::Attack2;
				break;
			case AttackStates::Attack2:
				break;
			}
			isAttacking = true;
			GetSprite()->SetLooping(false);
			if (CurrentAttack == AttackStates::None)
			{
				CurrentAttack = NextAttack;
				NextAttack = AttackStates::None;
				AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				PlayAttackSound(); // calls the blueprints associated with this event 
			}
		}
	}
	AttackCollision->Activate();
}


void ABasePlayer::FireProjectile()
{
	if (Mana > 0 && ProjectileSpawn)
	{
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = ProjectileSpawn->GetComponentLocation();
		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (ABaseProjectile* proj = GetWorld()->SpawnActor<ABaseProjectile>(Projectile, SpawnLocation, SpawnRotation, spawnParam))
		{
			newMana -= 10;
			proj = nullptr;
		}
	}
}

void ABasePlayer::PlayerHurt()
{
	HurtFlash = true;
	bHurt = true;
	GetSprite()->SetLooping(false);
	newHealth -= 10;

}

void ABasePlayer::Jump()
{
	if (isSliding == false)
	{
		ACharacter::Jump();
		if (GetCharacterMovement()->IsFalling() == false)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), JumpSound);
		}
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
		AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
	else if (isAttacking)
	{

		switch (NextAttack)
		{
		case AttackStates::None:
			isAttacking = false;
			CurrentAttack = AttackStates::None;
			GetSprite()->SetLooping(true);
			GetSprite()->Play();
			AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		default:
			CurrentAttack = NextAttack;
			NextAttack = AttackStates::None;
			GetSprite()->Play();
			AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

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
	if (bHurt)
	{
		bHurt = false;
		HurtFlash = false;
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
	Health = UKismetMathLibrary::Lerp(Health, newHealth, 0.1f);
	if (abs(Health - newHealth) < 1.f)
	{
		Health = newHealth;
	}
}

void ABasePlayer::AnimateManaChange()
{
	Mana = UKismetMathLibrary::Lerp(Mana, newMana, 0.1f);
	if (abs(Mana - newMana) < 1.f)
	{
		Mana = newMana;
	}
}



