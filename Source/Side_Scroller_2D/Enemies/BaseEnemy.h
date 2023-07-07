// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BaseEnemy.generated.h"

/**
 *
 */
UCLASS()
class SIDE_SCROLLER_2D_API ABaseEnemy : public APaperCharacter
{
	GENERATED_BODY()

public:

	ABaseEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void UpdateAnimation();
	void UpdateRotation();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Sprite")
		class UPaperFlipbook* m_IdleAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Sprite")
		class  UPaperFlipbook* m_RunAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Sprite")
		class UPaperFlipbook* m_HitAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Sprite")
		class UPaperFlipbook* m_DeathAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Sprite")
		class UPaperFlipbook* m_AttackAnimation;

	float m_Health; 

};
