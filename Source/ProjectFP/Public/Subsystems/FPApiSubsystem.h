// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FPApiSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFP_API UFPApiSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	FString MakeUrl ( const FString& Path ) const;

private:
	FString GetBaseUrl ( ) const;
};
