// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponAttachment.generated.h"


class UNiagaraComponent;
class ABasePlayer;
class ABaseProjectile;
class UArrowComponent;

UENUM(BlueprintType)
enum EMagicType
{
	Missile UMETA(DisplayName = "Missile"),
	Laser UMETA(DisplayName = "Laser"),

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

	TObjectPtr<ABasePlayer> PlayerRef;

	bool bBeamActive;

	float RelativeBeamYaw;
};
