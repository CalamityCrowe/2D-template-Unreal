// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelTemplate.h"
#include "PaperTileMapComponent.h"
#include "Side_Scroller_2D/Player/BasePlayer.h"
#include "UnrealClient.h"
#include "Kismet/GameplayStatics.h"
#include "Math/IntPoint.h"
#include "GameFramework/GameUserSettings.h"


ABaseLevelTemplate::ABaseLevelTemplate()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ABaseLevelTemplate::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{
		m_ViewportSize = UGameUserSettings::GetGameUserSettings()->GetScreenResolution();
	}
	FadeLevelIn(); 
}

void ABaseLevelTemplate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_Map)
	{


		if (GEngine && GEngine->GameViewport)
		{
			m_ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
		}
		m_Map->GetRenderComponent()->GetMapSize(m_MapWidth, m_MapHeight, m_Layers);
		//GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Red, FString::Printf(TEXT("Viewport Width %d"), m_ViewportSize.X));
		if (IsValid(m_PlayerRef))
		{
			if (m_PlayerRef->GetActorLocation().X <= m_ViewportSize.X / m_TileWidth)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Red, TEXT("Left"));
				m_PlayerRef->GetSpringArmComponent()->SocketOffset = FVector(m_PlayerRef->GetSocket().X, ((m_ViewportSize.X / m_TileWidth) - m_PlayerRef->GetActorLocation().X) + m_TileWidth, m_PlayerRef->GetSocket().Z);
				m_PlayerRef->GetSpringArmComponent()->bEnableCameraLag = false;
			}
			else if (m_PlayerRef->GetActorLocation().X >= (m_MapWidth * m_TileWidth) - (m_ViewportSize.X / m_TileWidth))
			{
				//GEngine->AddOnScreenDebugMessage(-1, .01f, FColor::Red, TEXT("Right"));
				m_PlayerRef->GetSpringArmComponent()->SocketOffset = FVector(m_PlayerRef->GetSocket().X, (m_MapWidth * m_TileWidth) - (m_ViewportSize.X / m_TileWidth) - m_PlayerRef->GetActorLocation().X, m_PlayerRef->GetSocket().Z);
				m_PlayerRef->GetSpringArmComponent()->bEnableCameraLag = false;
			}
			else
			{
				m_PlayerRef->GetSpringArmComponent()->SocketOffset = m_PlayerRef->GetSocket();
				m_PlayerRef->GetSpringArmComponent()->bEnableCameraLag = true;
			}
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Purple, FString::Printf(TEXT("Width: %d, Height: %d, Layers: %d"), m_MapWidth * m_TileWidth, m_MapHeight * m_TileHeight, m_Layers));
}

void ABaseLevelTemplate::FadeLevelIn()
{
}

