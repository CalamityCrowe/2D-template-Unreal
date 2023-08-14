// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Collectibles.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/AudioComponent.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"

// Sets default values
ABase_Collectibles::ABase_Collectibles()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Collision = CreateOptionalDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = m_Collision; // sets the root component to be the collider

	m_Audio = CreateOptionalDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	m_Audio->SetupAttachment(RootComponent);

	m_Sprite = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite0"));
	if (m_Sprite)
	{
		m_Sprite->SetupAttachment(m_Collision);
		m_Sprite->SetCollisionProfileName(FName(TEXT("CharacterMesh")));
		m_Sprite->SetGenerateOverlapEvents(false);
	}
}

// Called when the game starts or when spawned
void ABase_Collectibles::BeginPlay()
{
	Super::BeginPlay();

	m_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABase_Collectibles::CollectibleCollision);

}

// Called every frame
void ABase_Collectibles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABase_Collectibles::CollectibleCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Turquoise, FString(TEXT("Destroyed")));

	if (Cast<ABasePlayer>(OtherActor)) 
	{
		m_Audio->Play(); 
		Destroy(); // destroys the collectible when collided with the player
	}

}



