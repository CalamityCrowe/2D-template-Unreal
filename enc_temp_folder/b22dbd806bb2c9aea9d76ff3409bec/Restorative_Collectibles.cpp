// Fill out your copyright notice in the Description page of Project Settings.


#include "Restorative_Collectibles.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"
#include "Components/CapsuleComponent.h"


ARestorative_Collectibles::ARestorative_Collectibles() : ABase_Collectibles()
{
	m_CollectValue = 0;
}

void ARestorative_Collectibles::BeginPlay()
{
	ABase_Collectibles::BeginPlay();
	GetCollider()->OnComponentBeginOverlap.AddDynamic(this, &ARestorative_Collectibles::CollectibleCollision);
}

void ARestorative_Collectibles::Tick(float DeltaTime)
{
	ABase_Collectibles::Tick(DeltaTime);
}

void ARestorative_Collectibles::CollectibleCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABase_Collectibles::CollectibleCollision(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (TObjectPtr<ABasePlayer> tempPlayer = Cast<ABasePlayer>(OtherActor))
	{

		switch (m_CollectType)
		{
		case CollectType::Health:
			tempPlayer->RecoverHealth(m_CollectValue);
			break;
		}
	}
}
