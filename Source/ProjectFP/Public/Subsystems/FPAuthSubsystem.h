// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/IHttpRequest.h"
#include "GameMode/FPAuthTypes.h"
#include "FPAuthSubsystem.generated.h"

/**
 * 
 */
UCLASS( BlueprintType )
class PROJECTFP_API UFPAuthSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION ( BlueprintCallable , Category = "Auth" )
	void RegisterAccount ( const FString& UserID , const FString& Password /* , const FString& Nickname*/ );

	UFUNCTION ( BlueprintCallable , Category = "Auth" )
	void Login ( const FString& UserID , const FString& Password );

private:
	FString ApiBaseUrl = TEXT ( "http://127.0.0.1:3000" );

	void OnRegisterResponse ( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful );
	void OnLoginResponse ( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful );
};
