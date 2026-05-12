// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FPCharacterDef.generated.h"

class AFPCharacterBase;

USTRUCT ( BlueprintType )
struct FFPCharacterDef : public FTableRowBase
{
	GENERATED_BODY ( )

public:
	UPROPERTY ( EditAnywhere , BlueprintReadOnly )
	FText DisplayName;

	UPROPERTY ( EditAnywhere , BlueprintReadOnly )
	FName ElementType;

	UPROPERTY ( EditAnywhere , BlueprintReadOnly )
	TSoftClassPtr<AFPCharacterBase> CharacterClass;

	UPROPERTY ( EditAnywhere , BlueprintReadOnly )
	TSoftObjectPtr<UTexture2D> Icon;
};
