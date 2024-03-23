// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rendering/RenderingCommon.h"
#include "AccessibilitySettings.generated.h"


// an struct used for handling the colour vision deficiency settings
USTRUCT(BlueprintType)
struct SIDE_SCROLLER_2D_API FColourDeficiencyHandler
{
	GENERATED_BODY();
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EColorVisionDeficiency CurrentSetting = EColorVisionDeficiency::NormalVision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true, ClampMin = "0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float Intensity = 1.0f;
};

// an enum used for handling the size of text for the accessibility settings
UENUM()
enum class ETextSize : uint8

{
	TS_Small UMETA(DisplayName = "Small"),
	TS_Medium  UMETA(DisplayName = "Medium"),
	TS_Large UMETA(DisplayName = "Large"),
	TS_ExtraLarge UMETA(DisplayName = "Extra Large")
};

// a struct used for handling the text size for the accessibility settings
USTRUCT(BlueprintType)
struct SIDE_SCROLLER_2D_API FTextSettingHandler
{
	GENERATED_BODY();
public:
	void SetTextSize(ETextSize NewSize)
	{
		TextSize = NewSize;
	}
private:
	UPROPERTY(VisibleAnywhere, Category = "Text settings", meta = (AllowPrivateAccess = true))
	ETextSize TextSize = ETextSize::TS_Medium;

};

