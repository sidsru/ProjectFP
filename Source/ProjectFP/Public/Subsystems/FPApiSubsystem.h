// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "FPApiSubsystem.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_ThreeParams (FFPApiResponseDelegate, FHttpRequestPtr, FHttpResponsePtr, bool);

UCLASS()
class PROJECTFP_API UFPApiSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	FString MakeUrl ( const FString& Path ) const;


	void PostJson ( const FString& Path, const TSharedPtr<FJsonObject>& JsonObject, FFPApiResponseDelegate ResponseDelegate);
	void GetJson ( const FString& Path, FFPApiResponseDelegate ResponseDelegate);

private:
	FString GetBaseUrl ( ) const;
};
