// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FPPartyDataSubsystem.h"
#include "Subsystems/FPApiSubsystem.h"

#include "HttpModule.h"

void UFPPartyDataSubsystem::RequestOwnedCharacters ( int64 AccountID )
{
	UFPApiSubsystem* ApiSubsystem = GetGameInstance ( )->GetSubsystem<UFPApiSubsystem> ( );
	if ( !ApiSubsystem )
		return;

	ApiSubsystem->GetJson ( FString::Printf ( TEXT ( "/characters/owned?accountId=%lld" ) , AccountID ) ,
		FFPApiResponseDelegate::CreateUObject ( this , &UFPPartyDataSubsystem::OnOwnedCharactersResponse )
	);
}

void UFPPartyDataSubsystem::RequestCheckOwnedCharacter ( int64 AccountID , const FString& CharacterID )
{
	UFPApiSubsystem* ApiSubsystem = GetGameInstance ( )->GetSubsystem<UFPApiSubsystem> ( );
	if ( !ApiSubsystem )
		return;

	ApiSubsystem->GetJson ( FString::Printf ( TEXT ( "/characters/owned/check?accountId=%lld&characterId=%s" ) , AccountID , *CharacterID ) ,
		FFPApiResponseDelegate::CreateUObject ( this , &UFPPartyDataSubsystem::OnCheckOwnedCharacterResponse )
	);
}

void UFPPartyDataSubsystem::RequestAddOwnedCharacter ( int64 AccountId , const FString& CharacterId )
{
	UFPApiSubsystem* ApiSubsystem = GetGameInstance ( )->GetSubsystem<UFPApiSubsystem> ( );
	if ( !ApiSubsystem )
		return;

	TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject> ( );

	JsonObject->SetNumberField ( TEXT ( "accountId" ) , AccountId );
	JsonObject->SetStringField ( TEXT ( "character_code" ) , CharacterId );

	ApiSubsystem->PostJson ( TEXT ( "/characters/owned" ) , JsonObject ,
		FFPApiResponseDelegate::CreateUObject ( this , &UFPPartyDataSubsystem::OnAddOwnedCharacterResponse )
	);
}	

void UFPPartyDataSubsystem::OnOwnedCharactersResponse (FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful )
{
	if ( !bWasSuccessful || !Response.IsValid ( ) )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "OwnedCharacters request failed" ) );
		return;
	}

	const int32 StatusCode = Response->GetResponseCode ( );
	const FString ResponseString = Response->GetContentAsString ( );

	UE_LOG ( LogTemp , Display , TEXT ( "OwnedCharacters StatusCode: %d" ) , StatusCode );
	UE_LOG ( LogTemp , Display , TEXT ( "OwnedCharacters Response: %s" ) , *ResponseString );

	if ( StatusCode != 200 )
	{
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create ( ResponseString );

	if ( !FJsonSerializer::Deserialize ( Reader , JsonObject ) || !JsonObject.IsValid ( ) )
	{
		return;
	}

	bool bSuccess = false;
	JsonObject->TryGetBoolField ( TEXT ( "success" ) , bSuccess );

	if ( !bSuccess )
	{
		return;
	}

	const TArray<TSharedPtr<FJsonValue>>* OwnedArray = nullptr;

	if ( JsonObject->TryGetArrayField ( TEXT ( "ownedCharacters" ) , OwnedArray ) )
	{
		for ( const TSharedPtr<FJsonValue>& Value : *OwnedArray )
		{
			const TSharedPtr<FJsonObject> CharacterObject = Value->AsObject ( );
			if ( !CharacterObject.IsValid ( ) )
			{
				continue;
			}

			FString CharacterId = CharacterObject->GetStringField ( TEXT ( "character_id" ) );

			//UE_LOG ( LogTemp , Display , TEXT ( "Owned CharacterId: %s" ) , *CharacterId );
			PartyDataResultDelegate.Broadcast ( FName ( CharacterId ), true, FText::FromString ( TEXT ( "OwnedCharacter" ) ));
		}
	}
	LoadCompletedDelegate.Broadcast ( );
}

void UFPPartyDataSubsystem::OnCheckOwnedCharacterResponse ( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful )
{
	if ( !bWasSuccessful || !Response.IsValid ( ) )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "CheckOwnedCharacter request failed" ) );
		return;
	}

	const int32 StatusCode = Response->GetResponseCode ( );
	const FString ResponseString = Response->GetContentAsString ( );

	UE_LOG ( LogTemp , Display , TEXT ( "CheckOwnedCharacter StatusCode: %d" ) , StatusCode );
	UE_LOG ( LogTemp , Display , TEXT ( "CheckOwnedCharacter Response: %s" ) , *ResponseString );

	if ( StatusCode != 200 )
	{
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create ( ResponseString );

	if ( !FJsonSerializer::Deserialize ( Reader , JsonObject ) || !JsonObject.IsValid ( ) )
	{
		return;
	}

	bool bOwned = false;
	JsonObject->TryGetBoolField ( TEXT ( "owned" ) , bOwned );

	if ( bOwned )
	{
		UE_LOG ( LogTemp , Display , TEXT ( "This character is owned" ) );
	}
	else
	{
		UE_LOG ( LogTemp , Warning , TEXT ( "This character is not owned" ) );
	}
}

void UFPPartyDataSubsystem::OnAddOwnedCharacterResponse ( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful )
{
	if ( !bWasSuccessful || !Response.IsValid ( ) )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "AddOwnedCharacter request failed" ) );
		return;
	}

	const int32 StatusCode = Response->GetResponseCode ( );
	const FString ResponseString = Response->GetContentAsString ( );

	UE_LOG ( LogTemp , Display , TEXT ( "AddOwnedCharacter StatusCode: %d" ) , StatusCode );
	UE_LOG ( LogTemp , Display , TEXT ( "AddOwnedCharacter Response: %s" ) , *ResponseString );

	if ( StatusCode != 200 )
	{
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create ( ResponseString );

	if ( !FJsonSerializer::Deserialize ( Reader , JsonObject ) || !JsonObject.IsValid ( ) )
	{
		return;
	}

	FString Message;
	JsonObject->TryGetStringField ( TEXT ( "message" ) , Message );

	if ( Message == TEXT ( "CHARACTER_ADDED" ) )
	{
		UE_LOG ( LogTemp , Display , TEXT ( "Character added successfully" ) );
	}
	else if ( Message == TEXT ( "ALREADY_OWNED" ) )
	{
		UE_LOG ( LogTemp , Warning , TEXT ( "Character already owned" ) );
	}
}
