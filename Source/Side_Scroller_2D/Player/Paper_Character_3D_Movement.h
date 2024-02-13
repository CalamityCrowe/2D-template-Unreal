// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayer.h"
#include "Paper_Character_3D_Movement.generated.h"

/**
 * 
 */
UCLASS()
class SIDE_SCROLLER_2D_API APaper_Character_3D_Movement : public ABasePlayer
{
	GENERATED_BODY()
	
public:
	APaper_Character_3D_Movement(); 
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override; 

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	virtual void MovePlayer(const FInputActionValue&) override;

};
