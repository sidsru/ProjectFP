// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPPartyComponent.generated.h"

#pragma region ForwardDeclarations
class AFPPartyMemberState;
#pragma endregion

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTFP_API UFPPartyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPPartyComponent();

	virtual void GetLifetimeReplicatedProps ( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server, Reliable)
	void Server_RequestOwnedCharacters ();

	UFUNCTION(Server, Reliable)
	void Server_RequestSwapCharacter(int32 NewIndex);

	AFPPartyMemberState* GetActiveMember() const;
	AFPPartyMemberState* GetPartyMember ( int32 Index ) const;

	void InitializePartyOnServer();
protected:
	UPROPERTY ( ReplicatedUsing = OnRep_PartyMembers )
	TArray<TObjectPtr<AFPPartyMemberState>> PartyMembers;

	UPROPERTY ( ReplicatedUsing = OnRep_ActiveIndex )
	int32 ActiveIndex = 0;


	UPROPERTY ( Replicated )
	bool bSwapLocked = false;

	UFUNCTION ( )
	void OnRep_PartyMembers ( );

	UFUNCTION ( )
	void OnRep_ActiveIndex ( );

	bool CanSwapTo(int32 NewIndex) const;
	void ExecuteSwap(int32 NewIndex);
};
