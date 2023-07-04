// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperCharacter.h"
#include "BasePlayer.generated.h"

UCLASS()
class SIDE_SCROLLER_2D_API ABasePlayer : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateAnimations();
	void UpdateRotations();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetupAnimationStates();

	void MoveRight(float AxisInput);
	void CrouchInput();
	void UnCrouchInput();
	void Sliding(float X_Force, float upwardScale);

	UFUNCTION()
		void FinishedAnimation_Sliding();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_IdleAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_RunAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_CrouchAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_JumpAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_SlideAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_AttackAnimation1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_AttackAnimation2;





	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* m_Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		USpringArmComponent* m_SpringArmComponent;

	bool isSliding;

};
