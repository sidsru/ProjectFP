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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams ( FFPAuthRegisterResultDelegate, bool, bSuccess, FText, Message );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams ( FFPAuthLoginResultDelegate, bool, bSuccess, FText, Message );
UCLASS( BlueprintType )
class PROJECTFP_API UFPAuthSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION ( BlueprintCallable , Category = "Auth" )
	void RegisterAccount ( const FString& UserID , const FString& Password /* , const FString& Nickname*/ );

	UFUNCTION ( BlueprintCallable , Category = "Auth" )
	void Login ( const FString& UserID , const FString& Password );

	UPROPERTY ( BlueprintAssignable , Category = "Auth" )
	FFPAuthRegisterResultDelegate RegisterResultDelegate;

	UPROPERTY ( BlueprintAssignable , Category = "Auth" )
	FFPAuthLoginResultDelegate LoginResultDelegate;

public:
	void SetLoginSession ( int64 InAccountId, const FString& InUserID, const FString& InAccessToken );

	void ClearLoginSession ( );

	bool IsLoggedIn ( ) const;
	UFUNCTION ( BlueprintCallable , Category = "Auth" )
	int64 GetAccountId ( ) const;
	const FString& GetUserID ( ) const;
	const FString& GetAccessToken ( ) const;

private:

	void OnRegisterResponse ( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful );
	void OnLoginResponse ( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful );

private:
	int64 Account = -1;
	FString User;
	FString AccessToken;
};
