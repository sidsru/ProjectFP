// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "FPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFP_API UFPGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    void CreateSession();
    void InviteFriend();

protected:
    virtual void Init() override;

private:
    void OnCreateSessionComplete(FName SessionName, bool bSuccess);

    void OnInviteAccepted(bool bWasSuccessful, int32 ControllerId,
        TSharedPtr<const FUniqueNetId> UserId,
        const FOnlineSessionSearchResult& InviteResult);

    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};