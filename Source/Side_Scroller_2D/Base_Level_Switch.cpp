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

#if PLATFORM_WINDOWS
	CurrentPlatform = ECurrentPlatform::Windows;
#elif PLATFORM_PS5
	CurrentPlatform = ECurrentPlatform::PS5;
#else
	CurrentPlatform = ECurrentPlatform::None;
#endif
	bIsOverlapping = false;
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABase_Level_Switch::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ABase_Level_Switch::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABase_Level_Switch::BeginPlay()
{
	Super::BeginPlay();

	if (ButtonSelect->GetWidget() != nullptr)
	{
		ButtonSelect->SetVisibility(false);
	}
	WidgetStart = ButtonSelect->GetRelativeLocation();

}

// Called every frame
void ABase_Level_Switch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldBounce)
	{
		BounceOffset += DeltaTime;
		FVector NewLocation = FVector(WidgetStart.X, WidgetStart.Y, WidgetStart.Z + FMath::Sin(BounceOffset) * 5);
		ButtonSelect->SetRelativeLocation(NewLocation);
	}

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

	if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
	{
		if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PC->InputComponent))
		{
			PEI->BindAction(Player->GetInputData()->IA_Jump, ETriggerEvent::Started, this, &ABase_Level_Switch::SwitchLevel);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Level Switch Found"));
			PlayerReference = Player;
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
		bShouldBounce = true;
	}
}

void ABase_Level_Switch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ABasePlayer>(OtherActor))
	{
		ButtonSelect->SetVisibility(false);
		bShouldBounce = false;
		BounceOffset = 0;
	}
}

void ABase_Level_Switch::SwitchLevel()
{
	if (bIsOverlapping == true)
	{
		if (APlayerController* PC = Cast<APlayerController>(PlayerReference->GetController()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerController Valid"));
			if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LocalPlayer Valid"));
				if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())  // gets the enhanced input from the local input system
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InputSystem Valid"));
					InputSystem->ClearAllMappings();
				}
			}
			PC->PlayerCameraManager->StartCameraFade(0, 1, 3, FColor::Black,true,true );
			bIsTransitioning = true;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Level Switch Found"));
		}

	}
}

