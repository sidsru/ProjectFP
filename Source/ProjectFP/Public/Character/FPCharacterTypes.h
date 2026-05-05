// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPCharacterTypes.generated.h"

#pragma region Forward Declaration
class UInputAction;
#pragma endregion

USTRUCT(BlueprintType)
struct FInputActions
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> Move;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> Look;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> Jump;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> ZoomIn;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UInputAction> ZoomOut;
};
