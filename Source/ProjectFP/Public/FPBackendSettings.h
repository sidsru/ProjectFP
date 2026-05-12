// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FPBackendSettings.generated.h"

/**
 * 
 */
UCLASS( Config = Game , DefaultConfig )
class PROJECTFP_API UFPBackendSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	const FString& GetApiBaseUrl ( ) const
	{
		return ApiBaseUrl;
	}

private:
	UPROPERTY ( Config , EditDefaultsOnly , Category = "Backend" , meta = ( AllowPrivateAccess = "true" ) )
	FString ApiBaseUrl = TEXT ( "http://localhost:3000" );
};
