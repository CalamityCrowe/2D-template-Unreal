// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperCharacter.h"
#include "BasePlayer.generated.h"

class UWeaponAttachment;
class UInputMappingContext;
struct FInputActionValue;
class UInputConfigData;
class UCameraComponent;
class USphereComponent;
class ABaseProjectile;
class UPlayerAnimationComponent;

UENUM(BlueprintType)
enum class EAttackStates :uint8
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:

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

private:

	void MovePlayer(const FInputActionValue&);
	void CrouchInput(const FInputActionValue&);
	void UnCrouchInput(const FInputActionValue&);
	virtual void Jump() override;


	void LaunchPlayer(float X, float Vert);
	void MeleeInput();
	void Sliding();
	void UpdateRotations();


protected:

	UFUNCTION()
	void FinishedAnimation();


	UFUNCTION()
	void AttackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	void AnimateHealthChange();
	void AnimateManaChange();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerAnimationComponent> PlayerAnimationComponent;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Audio", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAudioComponent> Footsteps_Audio;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Audio", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> JumpSound;

	UPROPERTY(EditDefaultsOnly, Category = "Attack Collision", meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> AttackCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Projectiles", meta = (AllowPrivateAccess = true))
	TObjectPtr<UWeaponAttachment> WeaponSpawn; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArmComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float newHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Mana;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = true))
	float newMana;

	float MaxHealth, MaxMana;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack states", meta = (AllowPrivateAccess = true))
	TEnumAsByte<EAttackStates> CurrentAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack states", meta = (AllowPrivateAccess = true))
	TEnumAsByte<EAttackStates> NextAttack;

protected:
	bool bSliding;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	bool bAttacking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	bool bHurt;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	bool HurtFlash;

	bool PlayDeath = true;




public:



	USpringArmComponent* GetSpringArmComponent() { return SpringArmComponent; }

	UFUNCTION(BlueprintPure)
	float HealthPercentage() const
	{
		return Health / MaxHealth;
	}
	UFUNCTION(BlueprintPure)
	float ManaPercentage() const
	{
		return Mana / MaxMana;
	}

	float GetHealth()const { return Health; }
	float GetMana()const { return Mana;  }

	void IncreaseMaxHealth(float MH = 0) { MaxHealth += MH; newHealth += MH / 2; }
	void IncreaseMaxMana(float MM = 0) { MaxMana += MM; newMana += MM / 2; }
	void RecoverHealth(float H = 0) { newHealth += H; }
	void RecoverMana(float M = 0) { newMana += M; }
	void ReduceMana(float M) { newMana -= M; }


	FVector GetSocket() const { return SocketLocation; }

	bool IsHurt() const { return bHurt; }
	bool IsSliding() const { return bSliding; }
	bool IsAttacking() const { return bAttacking; }

	TEnumAsByte<EAttackStates> GetCurrentAttack() const { return CurrentAttack; }

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputConfigData> InputData;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	FVector SocketLocation;
public:
	TObjectPtr<UInputConfigData> GetInputData() const { return InputData; }

};
