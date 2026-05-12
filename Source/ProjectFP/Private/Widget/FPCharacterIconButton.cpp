// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FPCharacterIconButton.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UFPCharacterIconButton::NativeOnInitialized ( )
{
	Super::NativeOnInitialized ( );

	if ( ButtonCharacter )
	{
		ButtonCharacter->OnClicked.AddDynamic ( this, &UFPCharacterIconButton::HandleClicked );
	}
}

void UFPCharacterIconButton::InitCharacterIcon ( const FName& InCharacterCode , UTexture2D* InIcon , const FText& InDisplayName )
{
	CharacterCode = InCharacterCode;

	if ( ImageIcon && InIcon )
	{
		ImageIcon->SetBrushFromTexture ( InIcon );
	}

	if ( TextName )
	{
		TextName->SetText ( InDisplayName );
	}
}

void UFPCharacterIconButton::HandleClicked ( )
{
	OnCharacterIconClicked.Broadcast ( CharacterCode );
}
