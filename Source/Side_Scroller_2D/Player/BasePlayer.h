// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperCharacter.h"
#include "BasePlayer.generated.h"

UENUM(BlueprintType)
enum class AttackStates :uint8
{
	None UMETA(DisplayName = "None"),
	Attack1 UMETA(DisplayName = "Attack1"),
	Attack2 UMETA(DisplayName = "Attack2")

};

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

	UFUNCTION(BlueprintImplementableEvent)
		void PlayHitSound();
	UFUNCTION(BlueprintImplementableEvent)
		void PlayAttackSound();

	void PlayerHurt();
protected: 

	void SetupAnimationStates();

	void MoveRight(float AxisInput);
	void CrouchInput();
	void UnCrouchInput();
	void LaunchPlayer(float X, float Vert);
	void Sliding();
	void MeleeInput();

	void FireProjectile();



	virtual void Jump() override; 



	UFUNCTION(BlueprintAuthorityOnly)
		void FinishedAnimation_Attacking();
	UFUNCTION(BlueprintAuthorityOnly)
		void FinishedAnimation_Sliding();
	UFUNCTION(BlueprintAuthorityOnly)
		void FinishedAnimation_Hurt();

	UFUNCTION()
		void AttackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);




private:
	void AnimateHealthChange();

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_AttackAnimationSlide;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_HurtAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Sprites")
		class UPaperFlipbook* m_DeathAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Audio")
		class UAudioComponent* m_Footsteps_Audio;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Audio")
		class USoundBase* m_JumpSound; 

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<class ABaseProjectile> m_Projectile;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		class USphereComponent* m_ProjectileSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Attack Collision")
		class USphereComponent* m_AttackCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* m_Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		USpringArmComponent* m_SpringArmComponent;

	bool isSliding;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
		bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float m_Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float m_newHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float m_Mana;
	float m_MaxHealth, m_MaxMana;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack states")
		TEnumAsByte<AttackStates> m_CurrentAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack states")
		TEnumAsByte<AttackStates> m_NextAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
		bool m_isHurt;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
		bool m_HurtFlash;

	bool m_PlayDeath = true;

	float m_FlashMax;

	

public:

	FVector m_SocketLocation;


	USpringArmComponent* GetSpringArmComponent() { return m_SpringArmComponent; }

	UFUNCTION(BlueprintPure)
		float HealthPercentage()
	{
		return m_Health / m_MaxHealth;
	}
	UFUNCTION(BlueprintPure)
		float ManaPercentage()
	{
		return m_Mana / m_MaxMana;
	}

	bool isHurt() { return m_isHurt; }
};
