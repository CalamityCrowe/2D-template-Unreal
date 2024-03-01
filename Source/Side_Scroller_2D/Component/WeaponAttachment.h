// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponAttachment.generated.h"


class UNiagaraSystem;
class AScorch_Actor;
class UNiagaraComponent;
class ABasePlayer;
class ABaseProjectile;
class UArrowComponent;

UENUM(BlueprintType)
enum EMagicType
{
	Missile UMETA(DisplayName = "Missile"),
	Laser UMETA(DisplayName = "Laser"),
	ChaosSpawn UMETA(DisplayName = "Chaos")

};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIDE_SCROLLER_2D_API UWeaponAttachment : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponAttachment();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	virtual void SpawnProjectile();

	virtual void CastMagic();

	virtual void FireBeam();
private:
	bool LineTraceMethod(FVector StartPos, FVector EndPos, FHitResult&);


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupInput(ABasePlayer* PlayerRef);

	bool GetBeamActive() const { return bBeamActive; }

	UNiagaraComponent* GetBeamEffect() const { return BeamEffect; }

private:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TSubclassOf<ABaseProjectile> ProjectileRef;
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = true))
	float BeamSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TArray<float> ProjectileCosts;

	UPROPERTY(EditDefaultsOnly, Category = "Magic Type", meta = (AllowPrivateAccess = true));
	TEnumAsByte<EMagicType> CurrentMagic;

	UPROPERTY(EditDefaultsOnly, Category = "Niagara System", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraComponent> BeamEffect;

	UPROPERTY(EditDefaultsOnly,Category= "Niagara System", meta = (AllowPrivateAccess = true))
	TSubclassOf<AScorch_Actor> ScorchRef;

	UPROPERTY(EditDefaultsOnly, Category = "Niagara System", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> ImpactReference; 


	TObjectPtr<ABasePlayer> PlayerRef;

	bool bBeamActive;

	float RelativeBeamYaw;
};
