// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp_Collectibles.h"
#include "Components/CapsuleComponent.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"


APowerUp_Collectibles::APowerUp_Collectibles() :ABase_Collectibles()
{

}

void APowerUp_Collectibles::BeginPlay()
{
	ABase_Collectibles::BeginPlay();
	GetCollider()->OnComponentBeginOverlap.AddDynamic(this, &APowerUp_Collectibles::CollectibleCollision);  
}
void APowerUp_Collectibles::Tick(float DeltaTime)
{
	ABase_Collectibles::Tick(DeltaTime);
}

void APowerUp_Collectibles::CollectibleCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABase_Collectibles::CollectibleCollision(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (TObjectPtr<ABasePlayer>tempPlayer = Cast<ABasePlayer>(OtherActor)) 
	{
		tempPlayer->SpeedBoostTimer(5);
	}
}
