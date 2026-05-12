// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPCharacterIconButton.generated.h"

/**
 * 
 */
class UButton;
class UImage;
class UTextBlock;
class UTexture2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FFPOnCharacterIconClicked, const FName& , CharacterCode);

UCLASS()
class PROJECTFP_API UFPCharacterIconButton : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized ( ) override;
	void InitCharacterIcon ( const FName& InCharacterCode, UTexture2D* InIcon, const FText& InDisplayName );

public:
	UPROPERTY ( BlueprintAssignable )
	FFPOnCharacterIconClicked OnCharacterIconClicked;

protected:
	UPROPERTY ( meta = ( BindWidget ) )
	TObjectPtr<UButton> ButtonCharacter;

	UPROPERTY ( meta = ( BindWidget ) )
	TObjectPtr<UImage> ImageIcon;

	UPROPERTY ( meta = ( BindWidgetOptional ) )
	TObjectPtr<UTextBlock> TextName;

private:
	UFUNCTION ( )
	void HandleClicked ( );

private:
	FName CharacterCode;
};
