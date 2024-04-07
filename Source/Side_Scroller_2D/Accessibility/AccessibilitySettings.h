// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rendering/RenderingCommon.h"
#include "Styling/SlateColor.h"
#include "AccessibilitySettings.generated.h"


// an struct used for handling the colour vision deficiency settings
USTRUCT(BlueprintType)
struct SIDE_SCROLLER_2D_API FColourDeficiencyHandler
{
	GENERATED_BODY();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Current Deficiency")
	EColorVisionDeficiency CurrentSetting = EColorVisionDeficiency::NormalVision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Deficiency Intensity", meta = (ClampMin = "0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float Intensity = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Correct Deficiency")
	bool bCorrectDeficiency; // a bool used for determining whether the colour vision deficiency should be corrected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Show Correction with Deficiency")
	bool bShowCorrectionDeficiency; // a bool used for determining whether the colour vision deficiency should be corrected
};

// an enum used for handling the size of text for the accessibility settings
UENUM()
enum class ETextSize : uint8

{
	TS_Small = 9 UMETA(DisplayName = "Small"),
	TS_Medium = 11  UMETA(DisplayName = "Medium"),
	TS_Large = 13 UMETA(DisplayName = "Large"),
	TS_ExtraLarge = 15 UMETA(DisplayName = "Extra Large")
};

// a struct used for handling the text size for the accessibility settings
USTRUCT(BlueprintType)
struct SIDE_SCROLLER_2D_API FTextSettingHandler
{
	GENERATED_BODY();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Text settings", meta = (AllowPrivateAccess = true))
	ETextSize TextSize = ETextSize::TS_Medium;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Text Colour", meta = (AllowPrivateAccess = true))
	FSlateColor TextColour;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Text Colour", meta = (AllowPrivateAccess = true))
	FSlateColor BackgroundColour;

};

USTRUCT(BlueprintType)
struct SIDE_SCROLLER_2D_API FVisualSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTextSettingHandler TextSettings; // a struct used for handling the text settings for the accessibility settings
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FColourDeficiencyHandler ColourDeficiencySettings; // a struct used for handling the colour vision deficiency settings

};

// a struct used for handling the audio settings for the accessibility settings
USTRUCT(BlueprintType)
struct SIDE_SCROLLER_2D_API FAudioAccessibilitySettings
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio Subtitles", meta = (AllowPrivateAccess = true))
	bool bSubtitles = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio Subtitles", meta = (AllowPrivateAccess = true))
	bool bVisualCues = false;

public:
};

UCLASS()
class SIDE_SCROLLER_2D_API UAccessibilitySettings : public UObject
{
	GENERATED_BODY()

public:
	UAccessibilitySettings();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Accessibility Settings", meta = (AllowPrivateAccess = true))
	FVisualSettings VisualSettings; // a struct used for handling the visual settings for the accessibility settings
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Accessibility Settings", meta = (AllowPrivateAccess = true))
	FAudioAccessibilitySettings AudioSettings; // a struct used for handling the audio settings for the accessibility settings
public:
	FVisualSettings GetVisualSettings() const { return VisualSettings; }
	FAudioAccessibilitySettings GetAudioSettings() const { return AudioSettings; }
	void SetVisualSettings(const FVisualSettings& NewSettings) { VisualSettings = NewSettings; }
	void SetAudioSettings(const FAudioAccessibilitySettings& NewSettings) { AudioSettings = NewSettings; }
};