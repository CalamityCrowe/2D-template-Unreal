// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Level_Switch.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Inputs/InputConfigData.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BasePlayer.h"

// Sets default values
ABase_Level_Switch::ABase_Level_Switch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

	ButtonSelect = CreateOptionalDefaultSubobject<UWidgetComponent>(TEXT("Button Select"));
	ButtonSelect->SetupAttachment(Collider);






	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABase_Level_Switch::OnOverlapBegin);
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
	if (bIsTransitioning)
	{
		if (APlayerController* PC = Cast<APlayerController>(PlayerReference->GetController()))
		{
			if (PC->PlayerCameraManager->FadeTimeRemaining == 0 && PC->PlayerCameraManager->bEnableFading)
			{
				UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), LevelReference);
			}
		}
	}


}

void ABase_Level_Switch::SetupInputs(ABasePlayer* Player)
{
	if (Player)
	{
		PlayerReference = Player;

		if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
		{
			if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PC->InputComponent))
			{
				PEI->BindAction(Player->GetInputData()->IA_Jump, ETriggerEvent::Started, this, &ABase_Level_Switch::SwitchLevel);
			}
		}
	}
}

void ABase_Level_Switch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABasePlayer>(OtherActor))
	{
		ButtonSelect->SetVisibility(true);
		bIsOverlapping = true;
	}
}

void ABase_Level_Switch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ABasePlayer>(OtherActor))
	{
		ButtonSelect->SetVisibility(false);
		bIsOverlapping = false;
	}
}

void ABase_Level_Switch::SwitchLevel()
{
	if (bIsOverlapping)
	{
		if (IsValid(PlayerReference))
		{
			if (APlayerController* PC = Cast<APlayerController>(PlayerReference->GetController()))
			{
				if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
				{
					if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())  // gets the enhanced input from the local input system
					{
						InputSystem->ClearAllMappings();
					}
				}
				PC->PlayerCameraManager->StartCameraFade(0, 1, 3, FColor::Black, true, true);
				bIsTransitioning = true;
			}
		}

	}
}

