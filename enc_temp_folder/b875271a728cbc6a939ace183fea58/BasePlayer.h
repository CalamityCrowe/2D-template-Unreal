// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperCharacter.h"
#include "BasePlayer.generated.h"

class UCameraComponent;
class USphereComponent;
class ABaseProjectile;
class UPlayerAnimationComponent;

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

	void UpdateRotations();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Blueprint event implementation
	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitSound();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayAttackSound();
	UFUNCTION(BlueprintImplementableEvent)
	void SpeedBoostTimer(float timer);
	UFUNCTION(BlueprintImplementableEvent)
	void StrengthBoostTimer(float timer);
#pragma endregion

	void PlayerHurt();

protected:

	void SetupAnimationStates();

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
	void AnimateManaChange();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerAnimationComponent> PlayerAnimationComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Audio")
	TObjectPtr<UAudioComponent> Footsteps_Audio;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Audio")
	TObjectPtr<USoundBase> JumpSound;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ABaseProjectile> Projectile;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TObjectPtr<USphereComponent> ProjectileSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Attack Collision")
	TObjectPtr<USphereComponent> AttackCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	bool isSliding;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float newHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Mana;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Stats")
	float newMana;

	float MaxHealth, MaxMana;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack states")
	TEnumAsByte<AttackStates> CurrentAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack states")
	TEnumAsByte<AttackStates> NextAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	bool bHurt;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	bool HurtFlash;

	bool PlayDeath = true;

	float FlashMax;



public:

	FVector SocketLocation;


	USpringArmComponent* GetSpringArmComponent() { return SpringArmComponent; }

	UFUNCTION(BlueprintPure)
	float HealthPercentage()
	{
		return Health / MaxHealth;
	}
	UFUNCTION(BlueprintPure)
	float ManaPercentage()
	{
		return Mana / MaxMana;
	}

	void IncreaseMaxHealth(float MH = 0) { MaxHealth += MH; newHealth += MH / 2; }
	void IncreaseMaxMana(float MM = 0) { MaxMana += MM; newMana += MM / 2; }
	void RecoverHealth(float H = 0) { newHealth += H; }
	void RecoverMana(float M = 0) { newMana += M; }


	bool isHurt() { return bHurt; }
};
