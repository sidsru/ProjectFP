 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPCharacterList.generated.h"

/**
 * 
 */
class UWrapBox;
class UFPCharacterIconButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FFPOnCharacterSelected, const FName&, CharacterCode );

UCLASS()
class PROJECTFP_API UFPCharacterList : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct ( ) override;

	void RebuildCharacterList ( );

	void AddCharacterData ( FName ResultName ) { CharacterDatas.Add ( ResultName ); }
	void ClearCharacterData ( ) { CharacterDatas.Empty ( ); }

public:
	UPROPERTY ( BlueprintAssignable )
	FFPOnCharacterSelected OnCharacterSelected;
protected:
	UPROPERTY ( meta = ( BindWidget ) )
	TObjectPtr<UWrapBox> WrapBoxCharacters;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadOnly )
	TSubclassOf<UFPCharacterIconButton> CharacterIconButtonClass;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadOnly )
	TArray<FName> CharacterDatas;

private:
	UFUNCTION ( )
	void HandleCharacterIconClicked ( const FName& CharacterCode );
private:

	UPROPERTY ( EditDefaultsOnly , BlueprintReadOnly , Category = "Character" , meta = ( AllowPrivateAccess = "true" ) )
	TObjectPtr<UDataTable> CharacterDataTable;
};
