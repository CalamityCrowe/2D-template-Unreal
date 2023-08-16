// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Hazard.h"
#include "PaperFlipbookComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABase_Hazard::ABase_Hazard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Collision = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = m_Collision;

	m_Audio = CreateOptionalDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	m_Audio->SetupAttachment(m_Collision);

	m_Sprite = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	if (m_Sprite)
	{
		m_Sprite->SetupAttachment(m_Collision);
		m_Sprite->SetCollisionProfileName(FName(TEXT("CharacterMesh")));
		m_Sprite->SetGenerateOverlapEvents(false);
	}



}

// Called when the game starts or when spawned
void ABase_Hazard::BeginPlay()
{
	Super::BeginPlay();
	if (m_Collision)
	{
		m_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABase_Hazard::ColliderOverlap);
		m_Collision->OnComponentEndOverlap.AddDynamic(this, &ABase_Hazard::ColliderEndOverlap);
	}


}

// Called every frame
void ABase_Hazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABase_Hazard::ColliderOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(3, 2.0f, FColor::Silver, FString(TEXT("On Actor Begin Overlap with Hazard")));

}

void ABase_Hazard::ColliderEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(3, 2.0, FColor::Silver, FString(TEXT("On Actor End Overlap")));
}

