// Fill out your copyright notice in the Description page of Project Settings.


#include "PartySystem/FPPartyMemberState.h"
#include "Character/FPCharacterBase.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"

AFPPartyMemberState::AFPPartyMemberState ( )
{
	bReplicates = true;
	bOnlyRelevantToOwner = true;

}

void AFPPartyMemberState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPPartyMemberState, SlotIndex);
	DOREPLIFETIME(AFPPartyMemberState, CharacterId);
}

void AFPPartyMemberState::InitializeMember ( int32 InSlotIndex )
{
	if ( HasAuthority ( ) == false)
		return;

	SlotIndex = InSlotIndex;

	//if ( CharacterDefinition )
	//{
	//	CharacterId = CharacterDefinition->CharacterID;
	//}
}

TSubclassOf<AFPCharacterBase> AFPPartyMemberState::GetCharacterClass ( ) const
{
	//if ( !CharacterDefinition )
	//{
	//}
		return nullptr;

	//return CharacterDefinition->CharacterClass;
}

bool AFPPartyMemberState::CanBeSwappedIn ( ) const
{
	//if ( !IsAlive ( ) )
	//{
	//	return false;
	//}

	return true;
}

UAbilitySystemComponent* AFPPartyMemberState::GetAbilitySystemComponent() const
{
	return GetAbilitySystemComponent();
}

void AFPPartyMemberState::BeginPlay()
{
	Super::BeginPlay();

	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	}
}
