// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponAttachment.generated.h"


class ABasePlayer;
class ABaseProjectile;
class UArrowComponent;

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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupInput(ABasePlayer* PlayerRef);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TSubclassOf<ABaseProjectile> ProjectileRef;

	TObjectPtr<ABasePlayer> PlayerRef;
};
