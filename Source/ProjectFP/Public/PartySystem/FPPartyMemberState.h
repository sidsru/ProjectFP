// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "AbilitySystemInterface.h"
#include "FPPartyMemberState.generated.h"

/**
 * 
 */
class UFPCharacterDefinition;
class AFPCharacterBase;

UCLASS()
class PROJECTFP_API AFPPartyMemberState : public AInfo, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:

	AFPPartyMemberState ( );
	
	virtual void GetLifetimeReplicatedProps ( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	void InitializeMember ( int32 InSlotIndex);

	int32 GetSlotIndex ( ) const { return SlotIndex; }
	FName GetCharacterId ( ) const { return CharacterId; }

	TSubclassOf<AFPCharacterBase> GetCharacterClass ( ) const;

	bool CanBeSwappedIn ( ) const;

protected:

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;
private:

	UPROPERTY ( Replicated )
	int32 SlotIndex = INDEX_NONE;

	UPROPERTY ( Replicated )
	FName CharacterId = NAME_None;

};
