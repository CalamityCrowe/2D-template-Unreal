// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Regen.generated.h"

class UBoxComponent;
class UNiagaraComponent;
class ABasePlayer;

UCLASS()
class SIDE_SCROLLER_2D_API ABase_Regen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Regen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void RegenStats();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> Collision;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraComponent> RegenParticles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Particles", meta = (AllowPrivateAccess = true))
	FColor FirstParticleColor; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Particles", meta = (AllowPrivateAccess = true))
	FColor SecondParticleColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Particles", meta = (AllowPrivateAccess = true))
	float ParticleIntensity; 

	TObjectPtr<ABasePlayer> PlayerReference;

};
