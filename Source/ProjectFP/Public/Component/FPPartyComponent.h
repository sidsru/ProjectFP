// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPPartyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTFP_API UFPPartyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPPartyComponent();
	//void InitializePartyFromServer(/*const FServerPartySnapshot& PartySnapshot*/);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server, Reliable)
	void Server_RequestSwapCharacter(int32 NewIndex);

	//AFPPartyMemberState* GetActiveMember() const;

protected:
	//UPROPERTY(Replicated)
	//TArray<TObjectPtr<AFPPartyMemberState>> PartyMembers;

	//UPROPERTY(Replicated)
	//int32 ActiveIndex = 0;

	bool CanSwapTo(int32 NewIndex) const;
	void ExecuteSwap(int32 NewIndex);
};
