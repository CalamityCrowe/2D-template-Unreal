// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Rendering/RenderingCommon.h"
#include "Base_GameInstance.generated.h"

class UAccessibilitySettings;
class UGameUserSettings;

UCLASS()
class SIDE_SCROLLER_2D_API UBase_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBase_GameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Accessibility Settings")
	void SetAccessibilitySettings(UAccessibilitySettings* NewAccessibilitySettings);

	UFUNCTION(BlueprintImplementableEvent, Category = "Accessibility Settings")
	void ApplyColourDeficiency();



private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accessibility Settings", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAccessibilitySettings> AccessibilitySettings;


	TObjectPtr<UGameUserSettings> GameUserSettings;
};
