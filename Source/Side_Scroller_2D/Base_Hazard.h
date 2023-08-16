// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Hazard.generated.h"

UCLASS()
class SIDE_SCROLLER_2D_API ABase_Hazard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABase_Hazard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(Category = "Collider", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UBoxComponent> m_Collision;
	UPROPERTY(Category = "Audio", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UAudioComponent> m_Audio;
	UPROPERTY(Category = "Sprite", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UPaperFlipbookComponent> m_Sprite;

protected:

	UPROPERTY(Category = "Damage", VisibleAnywhere, BlueprintReadWrite)
		int m_Damage;


public:

	FORCEINLINE UBoxComponent* GetCollider() const { return m_Collision; }
	FORCEINLINE UAudioComponent* GetAudio() const { return m_Audio; }
	FORCEINLINE UPaperFlipbookComponent* GetSprite() const { return m_Sprite; }

	UFUNCTION()
		virtual void ColliderOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void ColliderEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
