// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelTemplate.h"
#include "PaperTileMapComponent.h"

ABaseLevelTemplate::ABaseLevelTemplate()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseLevelTemplate::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseLevelTemplate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_Map->GetRenderComponent()->GetMapSize(m_MapWidth, m_MapHeight, m_Layers);


	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Purple, FString::Printf(TEXT("Width: %d, Height: %d, Layers: %d"), m_MapWidth * m_TileWidth, m_MapHeight * m_TileHeight, m_Layers));
}
