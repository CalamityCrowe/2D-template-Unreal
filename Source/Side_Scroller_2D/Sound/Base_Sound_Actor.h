// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Sound_Actor.generated.h"

class UNiagaraComponent; 

UCLASS()
class SIDE_SCROLLER_2D_API ABase_Sound_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Sound_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> RippleEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara", meta = (AllowPrivateAccess = "true"))
	FLinearColor RippleColour;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Niagara", meta = (AllowPrivateAccess = "true"))
	float ColourIntensity;
};
