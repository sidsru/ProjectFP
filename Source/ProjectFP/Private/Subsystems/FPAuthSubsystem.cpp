#include "Subsystems/FPAuthSubsystem.h"

#include "HttpModule.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Interfaces/IHttpResponse.h"

void UFPAuthSubsystem::RegisterAccount (const FString& UserID ,const FString& Password/* , const FString& Nickname */)
{
	TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>( );// 제이슨 객체 생성
	JsonObject->SetStringField( TEXT( "UserID" ), UserID );
	JsonObject->SetStringField( TEXT( "Password" ), Password );
	//JsonObject->SetStringField( TEXT( "nickname" ), Nickname );

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create( &RequestBody );
	FJsonSerializer::Serialize( JsonObject, Writer ); // 제이슨 객체를 문자열로 변환

	TSharedRef<IHttpRequest> Request = FHttpModule::Get( ).CreateRequest ( );// HTTP 요청 생성

	Request->SetURL( ApiBaseUrl + TEXT( "/auth/register" ) ); // todo : 하드코딩된 URL 변수로 변경
	Request->SetVerb( TEXT( "POST" ) );
	Request->SetHeader( TEXT( "Content-Type" ), TEXT( "application/json" ) );
	Request->SetContentAsString( RequestBody );

	Request->OnProcessRequestComplete().BindUObject( this, &UFPAuthSubsystem::OnRegisterResponse );

	Request->ProcessRequest();
}

void UFPAuthSubsystem::OnRegisterResponse (FHttpRequestPtr Request ,FHttpResponsePtr Response ,bool bWasSuccessful )
{
	if ( !bWasSuccessful || !Response.IsValid ( ) )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "Register request failed." ) );
		return;
	}		

	const int32 StatusCode = Response->GetResponseCode ( );
	const FString ResponseBody = Response->GetContentAsString ( );

	UE_LOG ( LogTemp , Display , TEXT ( "Register StatusCode: %d" ) , StatusCode );
	UE_LOG ( LogTemp , Display , TEXT ( "Register Response: %s" ) , *ResponseBody );

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create ( ResponseBody );

	if ( !FJsonSerializer::Deserialize ( Reader , JsonObject ) || !JsonObject.IsValid ( ) )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "Failed to parse register response JSON." ) );
		return;
	}

	const bool bSuccess = JsonObject->GetBoolField ( TEXT ( "success" ) );

	if ( bSuccess )
	{
		const int32 AccountId = JsonObject->GetIntegerField ( TEXT ( "accountId" ) );
		UE_LOG ( LogTemp , Display , TEXT ( "Register success. AccountId: %d" ) , AccountId );
	}
	else
	{
		FString Error;
		JsonObject->TryGetStringField ( TEXT ( "error" ) , Error );
		UE_LOG ( LogTemp , Error , TEXT ( "Register failed. Error: %s" ) , *Error );
	}
}

void UFPAuthSubsystem::Login (const FString& UserID ,const FString& Password )
{
	TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject> ( );
	JsonObject->SetStringField ( TEXT ( "UserID" ) , UserID );
	JsonObject->SetStringField ( TEXT ( "Password" ) , Password );

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create ( &RequestBody );
	FJsonSerializer::Serialize ( JsonObject , Writer );

	TSharedRef<IHttpRequest> Request = FHttpModule::Get ( ).CreateRequest ( );

	Request->SetURL ( ApiBaseUrl + TEXT ( "/auth/login" ) );
	Request->SetVerb ( TEXT ( "POST" ) );
	Request->SetHeader ( TEXT ( "Content-Type" ) , TEXT ( "application/json" ) );
	Request->SetContentAsString ( RequestBody );

	Request->OnProcessRequestComplete ( ).BindUObject (
		this ,
		&UFPAuthSubsystem::OnLoginResponse
	);
	UE_LOG ( LogTemp , Warning , TEXT ( "Register RequestBody: %s" ) , *RequestBody );
	UE_LOG ( LogTemp , Warning , TEXT ( "Register UserID: [%s]" ) , *UserID );
	UE_LOG ( LogTemp , Warning , TEXT ( "Register Password: [%s]" ) , *Password );
	Request->ProcessRequest ( );
}

void UFPAuthSubsystem::OnLoginResponse (FHttpRequestPtr Request ,FHttpResponsePtr Response ,bool bWasSuccessful )
{
	if ( !bWasSuccessful || !Response.IsValid ( ) )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "Login request failed." ) );
		return;
	}

	const int32 StatusCode = Response->GetResponseCode ( );
	const FString ResponseBody = Response->GetContentAsString ( );

	UE_LOG ( LogTemp , Display , TEXT ( "Login StatusCode: %d" ) , StatusCode );
	UE_LOG ( LogTemp , Display , TEXT ( "Login Response: %s" ) , *ResponseBody );

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create ( ResponseBody );

	if ( !FJsonSerializer::Deserialize ( Reader , JsonObject ) || !JsonObject.IsValid ( ) )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "Failed to parse login response JSON." ) );
		return;
	}

	const bool bSuccess = JsonObject->GetBoolField ( TEXT ( "success" ) );

	if ( bSuccess )
	{
		const FString Token = JsonObject->GetStringField ( TEXT ( "token" ) );

		const TSharedPtr<FJsonObject>* AccountObject = nullptr;
		if ( JsonObject->TryGetObjectField ( TEXT ( "account" ) , AccountObject ) )
		{
			const int32 AccountId = ( *AccountObject )->GetIntegerField ( TEXT ( "accountId" ) );
			const FString UserID = ( *AccountObject )->GetStringField ( TEXT ( "UserID" ) );
			const FString Password = ( *AccountObject )->GetStringField ( TEXT ( "Password" ) );

			UE_LOG ( LogTemp , Display , TEXT ( "Login success." ) );
			UE_LOG ( LogTemp , Display , TEXT ( "AccountId: %d" ) , AccountId );
			UE_LOG ( LogTemp , Display , TEXT ( "UserID: %s" ) , *UserID );
			UE_LOG ( LogTemp , Display , TEXT ( "Password: %s" ) , *Password );
		}

		UE_LOG ( LogTemp , Display , TEXT ( "Token: %s" ) , *Token );
	}
	else
	{
		FString Error;
		JsonObject->TryGetStringField ( TEXT ( "error" ) , Error );
		UE_LOG ( LogTemp , Error , TEXT ( "Login failed. Error: %s" ) , *Error );
	}
}
