// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "U2D_AnimationContainer.generated.h"

class UPaperFlipbook;
/**
 * 
 */
UCLASS()
class SIDE_SCROLLER_2D_API UU2D_AnimationData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category= "Movement")
	TArray<UPaperFlipbook*> Movement_Animations; 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category= "Attacks")
	TArray<UPaperFlipbook*> Attack_Animations; 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category= "Miscellaneous")
	TArray<UPaperFlipbook*> Miscellaneous_Animations;
	
															
};
