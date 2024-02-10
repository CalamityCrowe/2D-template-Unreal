// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperCharacter.h"
#include "BasePlayer.generated.h"

class UInputMappingContext;
struct FInputActionValue;
class UInputConfigData;
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


	void FireProjectile();
	void LaunchPlayer(float X, float Vert);
	void MeleeInput();
	void Sliding();
	void SetupAnimationStates();
	void UpdateRotations();


protected:
	UFUNCTION()
	void FinishedAnimation_Attacking();
	UFUNCTION()
	void FinishedAnimation_Sliding();
	UFUNCTION()
	void FinishedAnimation_Hurt();

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

	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TSubclassOf<ABaseProjectile> Projectile;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile",meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> ProjectileSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Attack Collision", meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> AttackCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera",meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArmComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",meta = (AllowPrivateAccess = true))
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",meta = (AllowPrivateAccess = true))
	float newHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",meta = (AllowPrivateAccess = true))
	float Mana;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Stats",meta = (AllowPrivateAccess = true))
	float newMana;

	float MaxHealth, MaxMana;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack states",meta = (AllowPrivateAccess = true))
	TEnumAsByte<AttackStates> CurrentAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack states",meta = (AllowPrivateAccess = true))
	TEnumAsByte<AttackStates> NextAttack;

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


	FVector GetSocket() const { return SocketLocation; }

	bool IsHurt() const { return bHurt; }
	bool IsSliding() const { return bSliding; }
	bool IsAttacking() const { return bAttacking; }

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputConfigData> InputData;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	FVector SocketLocation;

};
