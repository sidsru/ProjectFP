// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/FPPartyComponent.h"
#include "PartySystem/FPPartyMemberState.h"
#include "Net/UnrealNetwork.h"
#include "PartySystem/FPCharacterDef.h"

// Sets default values for this component's properties
UFPPartyComponent::UFPPartyComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault ( true );
	// ...
}

void UFPPartyComponent::GetLifetimeReplicatedProps ( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps ( OutLifetimeProps );

	DOREPLIFETIME ( UFPPartyComponent , PartyMembers );
	DOREPLIFETIME ( UFPPartyComponent , ActiveIndex );
	DOREPLIFETIME ( UFPPartyComponent , bSwapLocked );

}

// Called when the game starts
void UFPPartyComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	if ( GetOwner ( ) && GetOwner ( )->HasAuthority ( ) )
	{
		InitializePartyOnServer ( );
	}
}

void UFPPartyComponent::Server_RequestOwnedCharacters_Implementation ( )
{

}

// Called every frame
//void UFPPartyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

void UFPPartyComponent::Server_RequestSwapCharacter_Implementation ( int32 NewIndex )
{
	ExecuteSwap ( NewIndex );
}

AFPPartyMemberState* UFPPartyComponent::GetActiveMember ( ) const
{
	if ( !PartyMembers.IsValidIndex ( ActiveIndex ) )
	{
		return nullptr;
	}
	return PartyMembers[ActiveIndex];//임시로 이렇게 했지만, 나중에 ActiveIndex가 유효한지 체크, 검증하는 로직이 필요할 듯
}

AFPPartyMemberState* UFPPartyComponent::GetPartyMember ( int32 Index ) const
{
	if ( !PartyMembers.IsValidIndex ( Index ) )
	{
		return nullptr;
	}

	return PartyMembers[Index];
}

void UFPPartyComponent::InitializePartyOnServer ( )
{
#pragma region Validation
	UWorld* World = GetWorld ( );
	if ( World == nullptr )
		return;

	if ( GetOwner ( ) == nullptr || GetOwner ( )->HasAuthority ( ) == false )
		return;

	if ( !PartyMembers.IsEmpty ( ) )
		return;

	APlayerController* OwnerController = Cast<APlayerController> ( GetOwner ( ) );
	if ( OwnerController == nullptr )
		return;
#pragma endregion

	constexpr int32 InitialPartySize = 3;

	for ( int32 i = 0; i < InitialPartySize; ++i )
	{
		AFPPartyMemberState* NewMember = World->SpawnActor<AFPPartyMemberState> ( );
		if ( NewMember == nullptr )
		{
			continue;
		}

		NewMember->SetOwner ( GetOwner ( ) );
		NewMember->InitializeMember ( i );

		PartyMembers.Add ( NewMember );
	}

	ActiveIndex = 0;
}

const FFPCharacterDef UFPPartyComponent::GetCharacterRow ( FName CharacterRowName )
{
	const FFPCharacterDef* CharacterDef =
		CharacterDataTable->FindRow<FFPCharacterDef> (
			CharacterRowName ,
			TEXT ( "Find Character Def" )
		);
	return *CharacterDef;
}

void UFPPartyComponent::OnRep_PartyMembers ( )
{
	// 클라이언트에서 파티 UI 갱신할 때 사용
}

void UFPPartyComponent::OnRep_ActiveIndex ( )
{
	// 클라이언트에서 현재 선택 캐릭터 UI 갱신
	// 예: 캐릭터 아이콘 하이라이트 변경
}

bool UFPPartyComponent::CanSwapTo ( int32 NewIndex ) const
{
	if ( bSwapLocked )
	{
		return false;
	}

	if ( !PartyMembers.IsValidIndex ( NewIndex ) )
	{
		return false;
	}

	if ( NewIndex == ActiveIndex )
	{
		return false;
	}

	AFPPartyMemberState* TargetMember = PartyMembers[NewIndex];
	if ( !IsValid ( TargetMember ) )
	{
		return false;
	}

	//if ( !TargetMember->CanBeSwappedIn ( ) )
	//{
	//	return false;
	//}

	return true;
}

void UFPPartyComponent::ExecuteSwap ( int32 NewIndex )
{
	if ( CanSwapTo ( NewIndex ) == false )
	{
		return;
	}

	ActiveIndex = NewIndex;

	// 나중에 여기서 실제 캐릭터 Pawn 교체/스폰/빙의 처리
	// 예:
	// Spawn active character pawn
	// Possess new pawn
	// Hide or destroy old pawn
}


