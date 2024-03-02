// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Level_Switch.generated.h"


class UWidgetComponent;
class UBoxComponent;
class ABasePlayer;
class ABaseLevelTemplate;

UENUM(BlueprintType)
enum class ECurrentPlatform : uint8
{
	None UMETA(DisplayName = "None"),
	Windows UMETA(DisplayName = "Windows"),
	PS5 UMETA(DisplayName = "PS5"),
};

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



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputs(ABasePlayer* Player);


private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Reference", meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UWorld> LevelReference;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> Collider;

	TObjectPtr<ABasePlayer> PlayerReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsOverlapping;
	bool bIsTransitioning;



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = true))
	TEnumAsByte<ECurrentPlatform> CurrentPlatform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> ButtonSelect;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SwitchLevel();

	FVector WidgetStart;
	float BounceOffset;
	bool bShouldBounce;



};

