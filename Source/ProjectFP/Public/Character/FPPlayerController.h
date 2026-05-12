// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPPlayerController.generated.h"

#pragma region ForwardDeclaration
class UInputMappingContext;
class UFPPartyComponent;
#pragma endregion

UCLASS()
class PROJECTFP_API AFPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AFPPlayerController ( );
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* pawn) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFPPartyComponent> PartyComponent;


};
