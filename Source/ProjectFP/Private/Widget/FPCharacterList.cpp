// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FPCharacterList.h"
#include "PartySystem/FPCharacterDef.h"

#include "Components/WrapBox.h"
#include "Components/WrapBoxSlot.h"
#include "Widget/FPCharacterIconButton.h"


void UFPCharacterList::NativeConstruct ( )
{
}

void UFPCharacterList::RebuildCharacterList ( )
{
	if ( !WrapBoxCharacters || !CharacterIconButtonClass )
	{
		return;
	}

	WrapBoxCharacters->ClearChildren ( );
	for(const FName& CharacterData : CharacterDatas)
	{
		UFPCharacterIconButton* Button = CreateWidget<UFPCharacterIconButton> ( GetOwningPlayer ( ) , CharacterIconButtonClass );

		const FFPCharacterDef* CharacterDef =
			CharacterDataTable->FindRow<FFPCharacterDef> (CharacterData, TEXT ( "Find Character Def" ));

		Button->OnCharacterIconClicked.AddDynamic ( this, &UFPCharacterList::HandleCharacterIconClicked );

		if ( Button )
		{
			Button->InitCharacterIcon ( CharacterData, CharacterDef->Icon.LoadSynchronous() , CharacterDef->DisplayName );
			UWrapBoxSlot* WrapSlot = WrapBoxCharacters->AddChildToWrapBox ( Button );

			if ( WrapSlot )
			{
				WrapSlot->SetPadding ( FMargin ( 5.0f ) );
			}
		}
	}
}

void UFPCharacterList::HandleCharacterIconClicked ( const FName& CharacterCode )
{
	OnCharacterSelected.Broadcast ( CharacterCode );
}
