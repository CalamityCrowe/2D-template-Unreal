// Fill out your copyright notice in the Description page of Project Settings.


#include "AccessibilitySettings.h"


UAccessibilitySettings::UAccessibilitySettings()
{
	VisualSettings.TextSettings.BackgroundColour = FColor::Transparent; // Default to transparent
	VisualSettings.TextSettings.TextColour = FColor::White; // Default to white
}
