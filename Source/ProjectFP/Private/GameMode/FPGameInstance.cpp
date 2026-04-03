// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FPGameInstance.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

void UFPGameInstance::CreateSession()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem) return;

	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	if (!Session.IsValid()) return;

	FOnlineSessionSettings Settings;
	Settings.bIsLANMatch = false;
	Settings.NumPublicConnections = 4;
	Settings.bAllowJoinInProgress = true;

	Settings.bUsesPresence = true;
	Settings.bUseLobbiesIfAvailable = true;

	Session->AddOnCreateSessionCompleteDelegate_Handle(
		FOnCreateSessionCompleteDelegate::CreateUObject(
			this,
			&UFPGameInstance::OnCreateSessionComplete
		)
	);

	Session->CreateSession(0, NAME_GameSession, Settings);
	UE_LOG(LogTemp, Warning, TEXT("CreateSession called"));
}

void UFPGameInstance::InviteFriend()
{
	IOnlineExternalUIPtr ExternalUI = Online::GetExternalUIInterface(GetWorld());

	if (ExternalUI.IsValid())
	{
		ExternalUI->ShowInviteUI(0, NAME_GameSession);
	}
}

void UFPGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Init called"));
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem) return;

	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	if (!Session.IsValid()) return;

	Session->AddOnSessionUserInviteAcceptedDelegate_Handle(
		FOnSessionUserInviteAcceptedDelegate::CreateUObject(
			this,
			&UFPGameInstance::OnInviteAccepted
		)
	);
	CreateSession();
}

void UFPGameInstance::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Session Created: %d"), bSuccess);
	if (bSuccess)
	{
		GetWorld()->ServerTravel("/Game/Map/TestLevel?listen");
		InviteFriend();
	}
}

void UFPGameInstance::OnInviteAccepted(bool bWasSuccessful, int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId, const FOnlineSessionSearchResult& InviteResult)
{
	if (!bWasSuccessful) return;

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem) return;

	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	if (!Session.IsValid()) return;

	Session->AddOnJoinSessionCompleteDelegate_Handle(
		FOnJoinSessionCompleteDelegate::CreateUObject(
			this,
			&UFPGameInstance::OnJoinSessionComplete
		)
	);

	Session->JoinSession(0, NAME_GameSession, InviteResult);
}

void UFPGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem) return;

	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	if (!Session.IsValid()) return;

	FString ConnectString;

	if (Session->GetResolvedConnectString(SessionName, ConnectString))
	{
		APlayerController* PC = GetFirstLocalPlayerController();

		if (PC)
		{
			PC->ClientTravel(ConnectString, TRAVEL_Absolute);
		}
	}
}
