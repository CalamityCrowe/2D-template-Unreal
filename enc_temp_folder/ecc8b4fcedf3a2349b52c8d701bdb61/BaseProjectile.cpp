// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	m_ProjectileMovement->ProjectileGravityScale = 0.0f;
	m_ProjectileMovement->MaxSpeed = 350.0f;
	m_ProjectileMovement->InitialSpeed = 350.f;

	m_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	m_Collision->SetSphereRadius(32.0f);
	RootComponent = m_Collision;


	m_ProjectileSprite = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	m_ProjectileSprite->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	m_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlapBegin);

}

void ABaseProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Destroy(); // destroys the actor 
	}
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


