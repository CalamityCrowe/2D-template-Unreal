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
#include "Side_Scroller_2D/Inputs/InputConfigData.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


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


	bSliding = false;
	bAttacking = false;


	MaxHealth = 100;
	Health = MaxHealth;
	newHealth = MaxHealth;
	MaxMana = 100;
	Mana = MaxMana;
	newMana = MaxMana;

	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasePlayer::AttackOverlap);

}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	SetupAnimationStates();
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

	if (APlayerController* PC = Cast<APlayerController>(GetController())) // tries to grab an instance of the player controller
	{
		if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer()) // gets the local player from the controller
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())  // gets the enhanced input from the local input system
			{
				InputSystem->ClearAllMappings(); // clears any mapping contexts if they had been assigned by mistake
				InputSystem->AddMappingContext(InputMappingContext, 0); // assigns the mapping contexts as the highest priority
			}
		}
	}

	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent)) // attempts to cast to the enhanced input system
	{


		if (InputData)
		{
			PEI->BindAction(InputData->IA_Movement, ETriggerEvent::Triggered, this, &ABasePlayer::MovePlayer);
			PEI->BindAction(InputData->IA_Jump, ETriggerEvent::Started, this, &ABasePlayer::Jump);
			//PEI->BindAction(InputData->IA_Crouch, ETriggerEvent::Started, this, &ABasePlayer::CrouchInput); 
			//PEI->BindAction(InputData->IA_Crouch, ETriggerEvent::Completed, this, &ABasePlayer::UnCrouchInput);
			//PEI->BindAction(InputData->IA_FireProjectile, ETriggerEvent::Started, this, &ABasePlayer::FireProjectile); 
			//PEI->BindAction(InputData->IA_Attack, ETriggerEvent::Started, this, &ABasePlayer::MeleeInput); 
			
		}

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

void ABasePlayer::CrouchInput(const FInputActionValue&)
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

void ABasePlayer::UnCrouchInput(const FInputActionValue&)
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
	bSliding = true;
	GetSprite()->SetLooping(false);
}

void ABasePlayer::MeleeInput()
{
	if (bSliding)
	{
		LaunchPlayer(300, 300);
		bAttacking = true;
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
			bAttacking = true;
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

void ABasePlayer::MovePlayer(const FInputActionValue& Val)
{
	const FVector2D InputAxis = Val.Get<FVector2D>(); // returns the input axis value
	if (Controller)
	{
		AddMovementInput(Camera->GetRightVector(), InputAxis.X);
	}
}

void ABasePlayer::Jump()
{
	if (bSliding == false)
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

	if (bAttacking && bSliding)
	{
		bAttacking = false;
		bSliding = false;
		GetSprite()->SetLooping(true);
		GetSprite()->Play();
		AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
	else if (bAttacking)
	{

		switch (NextAttack)
		{
		case AttackStates::None:
			bAttacking = false;
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
	if (bSliding && bAttacking == false)
	{
		bSliding = false;
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



