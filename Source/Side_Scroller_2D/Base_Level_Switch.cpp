// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Level_Switch.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BasePlayer.h"

// Sets default values
ABase_Level_Switch::ABase_Level_Switch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Collider = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Mesh);


}

// Called when the game starts or when spawned
void ABase_Level_Switch::BeginPlay()
{
	Super::BeginPlay();

	if ((PlayerReference = Cast<ABasePlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))))
	{

	}

}

// Called every frame
void ABase_Level_Switch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

