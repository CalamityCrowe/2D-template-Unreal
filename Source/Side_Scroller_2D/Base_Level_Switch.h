// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Level_Switch.generated.h"


class UBoxComponent;
class ABasePlayer;
class ABaseLevelTemplate;

UCLASS()
class SIDE_SCROLLER_2D_API ABase_Level_Switch : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABase_Level_Switch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void FadeLevelIn();
	UFUNCTION(BlueprintImplementableEvent)
	void FadeLevelOut();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Reference", meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UWorld> LevelReference;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> Collider;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Reference", meta = (AllowPrivateAccess = true))
	TObjectPtr<ABasePlayer> PlayerReference;


};
