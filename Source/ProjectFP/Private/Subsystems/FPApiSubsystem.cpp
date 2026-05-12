// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FPApiSubsystem.h"
#include "FPBackendSettings.h"

#include "HttpModule.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

FString UFPApiSubsystem::MakeUrl ( const FString& Path ) const
{
	FString BaseUrl = GetBaseUrl ( );

	if ( BaseUrl.EndsWith ( TEXT ( "/" ) ) )
	{
		BaseUrl.LeftChopInline ( 1 );
	}

	if ( Path.StartsWith ( TEXT ( "/" ) ) )
	{
		return BaseUrl + Path;
	}

	return BaseUrl + TEXT ( "/" ) + Path;
}

void UFPApiSubsystem::PostJson ( const FString& Path , const TSharedPtr<FJsonObject>& JsonObject , FFPApiResponseDelegate ResponseDelegate )
{
	if ( !JsonObject.IsValid ( ) )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "SendJsonRequest failed: JsonObject is invalid." ) );
		ResponseDelegate.ExecuteIfBound ( nullptr , nullptr , false );
		return;
	}

	FString RequestBody;

	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create ( &RequestBody );
	const bool bSerialized = FJsonSerializer::Serialize ( JsonObject.ToSharedRef ( ) , Writer );

	if ( !bSerialized )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "SendJsonRequest failed: Failed to serialize JsonObject." ) );
		ResponseDelegate.ExecuteIfBound ( nullptr , nullptr , false );
		return;
	}

	TSharedRef<IHttpRequest , ESPMode::ThreadSafe> Request = FHttpModule::Get ( ).CreateRequest ( );

	Request->SetURL ( MakeUrl ( Path ) );
	Request->SetVerb ( TEXT ( "POST" ) );
	Request->SetHeader ( TEXT ( "Content-Type" ) , TEXT ( "application/json" ) );
	Request->SetHeader ( TEXT ( "Accept" ) , TEXT ( "application/json" ) );
	Request->SetContentAsString ( RequestBody );

	Request->OnProcessRequestComplete ( ).BindLambda (
		[ ResponseDelegate ] ( FHttpRequestPtr RequestPtr , FHttpResponsePtr ResponsePtr , bool bWasSuccessful )
		{
			ResponseDelegate.ExecuteIfBound ( RequestPtr , ResponsePtr , bWasSuccessful );
		}
	);

	Request->ProcessRequest ( );
}

void UFPApiSubsystem::GetJson ( const FString& Path, FFPApiResponseDelegate ResponseDelegate )
{

	TSharedRef<IHttpRequest , ESPMode::ThreadSafe> Request = FHttpModule::Get ( ).CreateRequest ( );

	Request->SetURL ( MakeUrl ( Path ) );
	Request->SetVerb ( TEXT ( "GET" ) );
	Request->SetHeader ( TEXT ( "Content-Type" ) , TEXT ( "application/json" ) );

	Request->OnProcessRequestComplete ( ).BindLambda (
		[ ResponseDelegate ] ( FHttpRequestPtr RequestPtr , FHttpResponsePtr ResponsePtr , bool bWasSuccessful )
		{
			ResponseDelegate.ExecuteIfBound ( RequestPtr , ResponsePtr , bWasSuccessful );
		}
	);

	Request->ProcessRequest ( );
}

FString UFPApiSubsystem::GetBaseUrl ( ) const
{
	const UFPBackendSettings* BackendSettings = GetDefault<UFPBackendSettings>();
	if (BackendSettings == nullptr)
	{
		return TEXT ( "" );
	}
	return BackendSettings->GetApiBaseUrl();
}
