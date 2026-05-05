// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPAuthTypes.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FFPUserProfileSnapshot
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FString Nickname;

    UPROPERTY(BlueprintReadOnly)
    int32 Level = 1;

    UPROPERTY(BlueprintReadOnly)
    int32 Exp = 0;

    UPROPERTY(BlueprintReadOnly)
    int32 Gold = 0;
};

USTRUCT(BlueprintType)
struct FFPAuthResult
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FString AccessToken;

    UPROPERTY(BlueprintReadOnly)
    FString AccountId;

    UPROPERTY(BlueprintReadOnly)
    FFPUserProfileSnapshot Profile;
};