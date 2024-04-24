// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "PaperTileMapActor.h"
#include "BaseLevelTemplate.generated.h"

/**
 *
 */
UCLASS()
class SIDE_SCROLLER_2D_API ABaseLevelTemplate : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	ABaseLevelTemplate();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Map")
	class APaperTileMapActor* m_Map;

	int32 m_MapWidth, m_MapHeight, m_Layers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Map")
	int m_TileWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Map")
	int m_TileHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Ref")
	class ABasePlayer* m_PlayerRef;

	FIntPoint m_ViewportSize;

private:

	void FadeLevelIn();

};
