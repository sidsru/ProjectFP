// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPPlayerController.h"
#include "EnhancedInputSubsystems.h"

void AFPPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (PlayerCameraManager)
	{
		PlayerCameraManager->ViewPitchMax = 45.f;
		PlayerCameraManager->ViewPitchMin = -60.f;
	}
}

void AFPPlayerController::BeginPlay()
{
}

void AFPPlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess"));

	if (!IsLocalController()) 
		return;

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer)
		return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem)
		return;

	Subsystem->ClearAllMappings();
	if (IMC)
	{
		Subsystem->AddMappingContext(IMC, 0);
	}
}
