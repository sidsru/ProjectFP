// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPPartyFormation.generated.h"

/**
 * 
 */
class UButton;
class UFPCharacterList;
UCLASS()
class PROJECTFP_API UFPPartyFormation : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct ( ) override;
	UFUNCTION ( )
	void OnSlotClicked1 (  );
	UFUNCTION ( )
	void OnSlotClicked2 (  );
	UFUNCTION ( )
	void OnSlotClicked3 (  );

	void OnSlot ( int32 Index );

	UFUNCTION ( )
	void HandleCharacterDataResult ( FName ResultName , bool bSuccess , FText Message );

	UFUNCTION ( )
	void HandleOwnedCharactersLoadCompleted ( );

	void SetPartySlotsEnabled ( bool bEnabled );

	UFUNCTION ( )
	void HideCharacterList ( const FName& CharacterCode );

public:
	UPROPERTY ( meta = ( BindWidget ) )
	TObjectPtr<UButton> Slot1;

	UPROPERTY ( meta = ( BindWidget ) )
	TObjectPtr<UButton> Slot2;

	UPROPERTY ( meta = ( BindWidget ) )
	TObjectPtr<UButton> Slot3;

	UPROPERTY ( meta = ( BindWidget ) )
	TObjectPtr<UUserWidget> CharacterList;
private:

	UPROPERTY ( )
	bool bOwnedCharactersLoaded = false;

	int32 SlotIndex = -1;
};
