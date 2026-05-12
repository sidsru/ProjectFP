#include "Subsystems/FPAuthSubsystem.h"

#include "Subsystems/FPApiSubsystem.h"
#include "HttpModule.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Interfaces/IHttpResponse.h"

void UFPAuthSubsystem::RegisterAccount ( const FString& UserID , const FString& Password )
{
	TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject> ( );// 제이슨 객체 생성

	JsonObject->SetStringField ( TEXT ( "UserID" ) , UserID );
	JsonObject->SetStringField ( TEXT ( "Password" ) , Password );

	UGameInstance* GameInstance = GetGameInstance ( );
	if ( !GameInstance )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "RequestRegister failed: GameInstance is null." ) );
		return;
	}

	UFPApiSubsystem* ApiSubsystem = GameInstance->GetSubsystem<UFPApiSubsystem> ( );
	if ( !ApiSubsystem )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "RequestRegister failed: ApiSubsystem is null." ) );
		return;
	}
	//Api서브시스템에 HTTP 요청을 보내는 부분
	ApiSubsystem->PostJson ( TEXT ( "/auth/register" ) , JsonObject ,
		FFPApiResponseDelegate::CreateUObject (
			this ,
			&UFPAuthSubsystem::OnRegisterResponse
		)
	);

}

void UFPAuthSubsystem::OnRegisterResponse ( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful )
{
	if ( !bWasSuccessful || !Response.IsValid ( ) )
	{
		RegisterResultDelegate.Broadcast ( false , FText::FromString ( "Register request failed." ) );
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
		RegisterResultDelegate.Broadcast ( false , FText::FromString ( "Failed to parse register response JSON." ) );
		return;
	}

	const bool bSuccess = JsonObject->GetBoolField ( TEXT ( "success" ) );

	if ( bSuccess )
	{
		const int32 AccountId = JsonObject->GetIntegerField ( TEXT ( "accountId" ) );
		RegisterResultDelegate.Broadcast ( true , FText::FromString ( "Register success." ) );
	}
	else
	{
		FString Error;
		JsonObject->TryGetStringField ( TEXT ( "error" ) , Error );
		RegisterResultDelegate.Broadcast ( false , FText::FromString ( FString::Printf ( TEXT ( "Register failed. Error: %s" ) , *Error ) ) );
	}
}

void UFPAuthSubsystem::Login ( const FString& UserID , const FString& Password )
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject> ( );

	JsonObject->SetStringField ( TEXT ( "UserID" ) , UserID );
	JsonObject->SetStringField ( TEXT ( "Password" ) , Password );

	UGameInstance* GameInstance = GetGameInstance ( );
	if ( !GameInstance )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "RequestRegister failed: GameInstance is null." ) );
		return;
	}

	UFPApiSubsystem* ApiSubsystem = GameInstance->GetSubsystem<UFPApiSubsystem> ( );
	if ( !ApiSubsystem )
	{
		UE_LOG ( LogTemp , Error , TEXT ( "RequestRegister failed: ApiSubsystem is null." ) );
		return;
	}

	if ( !ApiSubsystem )
	{
		return;
	}

	ApiSubsystem->PostJson ( TEXT ( "/auth/login" ) , JsonObject ,
		FFPApiResponseDelegate::CreateUObject (
			this ,
			&UFPAuthSubsystem::OnLoginResponse
		)
	);
}

void UFPAuthSubsystem::OnLoginResponse ( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bWasSuccessful )
{
	if ( !bWasSuccessful || !Response.IsValid ( ) )
	{
		LoginResultDelegate.Broadcast ( false , FText::FromString ( "Login request failed." ) );
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
		LoginResultDelegate.Broadcast ( false , FText::FromString ( "Failed to parse login response JSON." ) );
		return;
	}

	const bool bSuccess = JsonObject->GetBoolField ( TEXT ( "success" ) );

	if ( bSuccess )
	{
		const FString Token = JsonObject->GetStringField ( TEXT ( "accessToken" ) );

		const TSharedPtr<FJsonObject>* AccountObject = nullptr;
		if ( JsonObject->TryGetObjectField ( TEXT ( "account" ) , AccountObject ) )
		{
			const int32 AccountId = ( *AccountObject )->GetIntegerField ( TEXT ( "account_id" ) );
			const FString UserID = ( *AccountObject )->GetStringField ( TEXT ( "UserID" ) );

			UE_LOG ( LogTemp , Display , TEXT ( "AccountId: %d" ) , AccountId );
			UE_LOG ( LogTemp , Display , TEXT ( "UserID: %s" ) , *UserID );
			SetLoginSession ( AccountId , UserID , Token );
		}

		LoginResultDelegate.Broadcast ( true , FText::FromString ( "Login success." ) );
	}
	else
	{
		FString Error;
		JsonObject->TryGetStringField ( TEXT ( "error" ) , Error );
		LoginResultDelegate.Broadcast ( false , FText::FromString ( Error ) );
	}
}

void UFPAuthSubsystem::SetLoginSession ( int64 InAccountId , const FString& InUserID , const FString& InAccessToken )
{
	Account = InAccountId;
	User = InUserID;
	AccessToken = InAccessToken;
}

void UFPAuthSubsystem::ClearLoginSession ( )
{
	Account = -1;
	User.Empty ( );
	AccessToken.Empty ( );
}

bool UFPAuthSubsystem::IsLoggedIn ( ) const
{
	return Account > 0 && !AccessToken.IsEmpty ( );
}

int64 UFPAuthSubsystem::GetAccountId ( ) const
{
	return Account;
}

const FString& UFPAuthSubsystem::GetUserID ( ) const
{
	return User;
}

const FString& UFPAuthSubsystem::GetAccessToken ( ) const
{
	return AccessToken;
}
