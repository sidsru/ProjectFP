// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FPPartyFormation.h"
#include "Widget/FPCharacterList.h"
#include "Subsystems/FPPartyDataSubsystem.h"
#include "Subsystems/FPAuthSubsystem.h"

#include "Components/Button.h"

void UFPPartyFormation::NativeConstruct ( )
{
	Super::NativeConstruct ( );

	bOwnedCharactersLoaded = false;
	SlotIndex = -1;

	UFPPartyDataSubsystem* PartyDataSubsystem = GetGameInstance ( )->GetSubsystem<UFPPartyDataSubsystem> ( );
	UFPAuthSubsystem* AuthSubsystem = GetGameInstance ( )->GetSubsystem<UFPAuthSubsystem> ( );

	UFPCharacterList* FPCharacterList = Cast<UFPCharacterList> ( CharacterList );
	if ( FPCharacterList )
	{
		FPCharacterList->ClearCharacterData ( );
		FPCharacterList->OnCharacterSelected.AddDynamic ( this , &UFPPartyFormation::HideCharacterList );
	}
	SetPartySlotsEnabled ( false );
	PartyDataSubsystem->PartyDataResultDelegate.AddUniqueDynamic ( this , &UFPPartyFormation::HandleCharacterDataResult );
	PartyDataSubsystem->LoadCompletedDelegate.AddUniqueDynamic ( this, &UFPPartyFormation::HandleOwnedCharactersLoadCompleted );

	if ( Slot1 )
	{
		Slot1->OnClicked.AddDynamic ( this , &UFPPartyFormation::OnSlotClicked1 );
	}
	if ( Slot2 )
	{
		Slot2->OnClicked.AddDynamic ( this , &UFPPartyFormation::OnSlotClicked2 );
	}
	if ( Slot3 )
	{
		Slot3->OnClicked.AddDynamic ( this , &UFPPartyFormation::OnSlotClicked3 );
	}
	PartyDataSubsystem->RequestOwnedCharacters ( AuthSubsystem->GetAccountId ( ) );
}

void UFPPartyFormation::OnSlotClicked1 ( )
{
	if ( bOwnedCharactersLoaded )
	{
		OnSlot ( 0 );
	}
}

void UFPPartyFormation::OnSlotClicked2 ( )
{
	if ( bOwnedCharactersLoaded )
	{
		OnSlot ( 1 );
	}
}

void UFPPartyFormation::OnSlotClicked3 ( )
{
	if ( bOwnedCharactersLoaded )
	{
		OnSlot ( 2 );
	}
}

void UFPPartyFormation::OnSlot ( int32 Index )
{
	SlotIndex = Index;
	UE_LOG ( LogTemp , Display , TEXT ( "Index = %d" ), Index );
	CharacterList->SetVisibility ( ESlateVisibility::Visible );
}

void UFPPartyFormation::HandleCharacterDataResult ( FName ResultName , bool bSuccess , FText Message )
{
	if ( bSuccess )
	{
		UFPCharacterList* FPCharacterList = Cast<UFPCharacterList> ( CharacterList );

		if ( FPCharacterList )
		{
			FPCharacterList->AddCharacterData ( ResultName );
		}
	}
	else
	{
		UE_LOG ( LogTemp , Error , TEXT ( "Failed to get character data: %s" ) , *Message.ToString ( ) );
	}
}

void UFPPartyFormation::HandleOwnedCharactersLoadCompleted ( )
{
	bOwnedCharactersLoaded = true;

	SetPartySlotsEnabled ( true );

	UFPCharacterList* FPCharacterList = Cast<UFPCharacterList> ( CharacterList );
	if ( FPCharacterList )
	{
		FPCharacterList->RebuildCharacterList ( );
	}

	UE_LOG ( LogTemp , Display , TEXT ( "Owned characters load completed." ) )
}

void UFPPartyFormation::SetPartySlotsEnabled ( bool bEnabled )
{
	if ( Slot1 )
	{
		Slot1->SetIsEnabled ( bEnabled );
	}

	if ( Slot2 )
	{
		Slot2->SetIsEnabled ( bEnabled );
	}

	if ( Slot3 )
	{
		Slot3->SetIsEnabled ( bEnabled );
	}
}

void UFPPartyFormation::HideCharacterList ( const FName& CharacterCode )
{
	CharacterList->SetVisibility ( ESlateVisibility::Hidden );
}

