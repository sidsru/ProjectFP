// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FPApiSubsystem.h"
#include "FPBackendSettings.h"

FString UFPApiSubsystem::MakeUrl ( const FString& Path ) const
{
    return GetBaseUrl() + Path;
}

FString UFPApiSubsystem::GetBaseUrl ( ) const
{
	const UFPBackendSettings* BackendSettings = GetDefault<UFPBackendSettings>();
	if (BackendSettings == nullptr)
	{
		return TEXT ( "" );
	}
	return BackendSettings->GetApiBaseUrl();
}
