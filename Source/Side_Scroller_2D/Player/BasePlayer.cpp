// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

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
	
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	//m_Sprites = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Sprites")); 



}

void ABasePlayer::UpdateAnimations()
{
	const FVector PlayerVelocity = GetVelocity(); 
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared(); // gets the length of the velocity squared

	UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? m_RunAnimation : m_IdleAnimation;
	DesiredAnimation = (abs(PlayerVelocity.Z) > 0.0f) ? m_JumpAnimation : DesiredAnimation; 

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
			GetController()->SetControlRotation(FRotator(0, 180,0));
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

}

