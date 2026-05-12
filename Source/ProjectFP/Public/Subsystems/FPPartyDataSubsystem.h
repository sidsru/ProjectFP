// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "FPPartyDataSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams ( FFPPartyDataResultDelegate , FName , ResultName , bool, bSuccess , FText , Message );
DECLARE_DYNAMIC_MULTICAST_DELEGATE ( FFPLoadCompletedDelegate );
UCLASS( BlueprintType )
class PROJECTFP_API UFPPartyDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION ( BlueprintCallable , Category = "Auth" )
	void RequestOwnedCharacters ( int64 AccountID );
	UFUNCTION ( BlueprintCallable , Category = "Auth" )
	void RequestCheckOwnedCharacter ( int64 AccountID , const FString& CharacterID );
	UFUNCTION ( BlueprintCallable , Category = "Auth" )
	void RequestAddOwnedCharacter ( int64 AccountId , const FString& CharacterId );

	UPROPERTY ( BlueprintAssignable , Category = "Auth" )
	FFPPartyDataResultDelegate PartyDataResultDelegate;
	UPROPERTY ( BlueprintAssignable , Category = "Auth" )
	FFPLoadCompletedDelegate LoadCompletedDelegate;
private:
	void OnOwnedCharactersResponse ( FHttpRequestPtr Request ,FHttpResponsePtr Response ,bool bWasSuccessful );
	void OnCheckOwnedCharacterResponse ( FHttpRequestPtr Request ,FHttpResponsePtr Response ,bool bWasSuccessful );
	void OnAddOwnedCharacterResponse ( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful );
};
