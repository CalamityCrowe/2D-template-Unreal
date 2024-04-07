// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_GameInstance.h"

#include "MovieSceneTracksPropertyTypes.h"
#include "GameFramework/GameUserSettings.h"
#include "Side_Scroller_2D/Accessibility/AccessibilitySettings.h"
#include "SlateCore/Public/Brushes/SlateColorBrush.h"

UBase_GameInstance::UBase_GameInstance()
{
}

void UBase_GameInstance::Init()
{
	Super::Init();
}

void UBase_GameInstance::SetAccessibilitySettings(UAccessibilitySettings* NewAccessibilitySettings) 
{
}


