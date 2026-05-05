// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FPCharacterTypes.h"
#include "FPCharacterBase.generated.h"

#pragma region Forward Declaration
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
#pragma endregion

UCLASS()
class PROJECTFP_API AFPCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPCharacterBase();
#pragma region component
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;
#pragma endregion

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MinArmLength;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MaxArmLength;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	FVector MinArmLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	FVector MaxArmLocation;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Input
#pragma region InputFunction
public:

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void ZoomIn();

	UFUNCTION()
	void ZoomOut();


#pragma endregion
protected:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FInputActions Actions;
#pragma endregion
};
