// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Component/FPPartyComponent.h"

AFPPlayerController::AFPPlayerController ( )
{
	PartyComponent = CreateDefaultSubobject<UFPPartyComponent> ( TEXT ( "PartyComponent" ) );
}

void AFPPlayerController::PostInitializeComponents ( )
{
	Super::PostInitializeComponents ( );
	if ( PlayerCameraManager )
	{
		PlayerCameraManager->ViewPitchMax = 45.f;
		PlayerCameraManager->ViewPitchMin = -60.f;
	}
}

void AFPPlayerController::BeginPlay ( )
{
}

void AFPPlayerController::OnPossess ( APawn* pawn )
{
	Super::OnPossess ( pawn );
	if ( !IsLocalController ( ) )
		return;

	ULocalPlayer* LocalPlayer = GetLocalPlayer ( );
	if ( !LocalPlayer )
		return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem> ( );
	if ( !Subsystem )
		return;

	Subsystem->ClearAllMappings ( );
	if ( IMC )
	{
		Subsystem->AddMappingContext ( IMC , 0 );
	}
}

