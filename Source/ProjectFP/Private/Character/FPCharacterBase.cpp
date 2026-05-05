// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

// Sets default values
AFPCharacterBase::AFPCharacterBase() :
	MinArmLength(70.f),
	MaxArmLength(450.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = false;
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -90.f),
		FRotator(0.f, -90.f, 0.f));
	GetMesh()->VisibilityBasedAnimTickOption =
		EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered; // 화면에 보일때만 에니메이션 업데이트
#pragma region SpringArm

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->TargetArmLength = 450.f;
	SpringArmComp->SetRelativeLocation(FVector(0.f, 0.f, 35.f));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true; // 카메라가 캐릭터를 뒤늦게 따라옴
	SpringArmComp->CameraLagSpeed = 5.0f; // 따라오는 속도
	SpringArmComp->CameraLagMaxDistance = 80.0f; // 카메라와 본래 위치와의 최대 거리 차이
	//78.0
#pragma endregion

#pragma region Camera

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComp);
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.f, 0.0f);

#pragma endregion
}

// Called when the game starts or when spawned
void AFPCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Controller: %s"), *GetNameSafe(GetController()));
}

// Called every frame
//void AFPCharacterBase::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void AFPCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UE_LOG(LogTemp, Display, TEXT("SetupInputComp"));

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComp) == false)
		return;

	EnhancedInputComp->BindAction(Actions.Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComp->BindAction(Actions.Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComp->BindAction(Actions.Jump, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComp->BindAction(Actions.Jump, ETriggerEvent::Canceled, this, &ThisClass::StopJumping);
	EnhancedInputComp->BindAction(Actions.ZoomIn,ETriggerEvent::Triggered, this, &ThisClass::ZoomIn);
	EnhancedInputComp->BindAction(Actions.ZoomOut, ETriggerEvent::Triggered, this, &ThisClass::ZoomOut);
}

void AFPCharacterBase::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::Y);

	if (FMath::IsNearlyZero(MovementVector.X) == false)
	{
			AddMovementInput(ForwardDirection, MovementVector.X);
	}

	if (FMath::IsNearlyZero(MovementVector.Y) == false)
	{
		AddMovementInput(RightDirection, MovementVector.Y);
	}

}

void AFPCharacterBase::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (FMath::IsNearlyZero(LookAxisVector.Y) == false)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
	if (FMath::IsNearlyZero(LookAxisVector.X) == false)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
}
void AFPCharacterBase::ZoomIn()
{
	if (!IsValid(SpringArmComp))
	{
		return;
	}
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	const float TargetLength = MinArmLength;
	SpringArmComp->TargetArmLength = FMath::FInterpTo(
		SpringArmComp->TargetArmLength,
		TargetLength,
		DeltaTime,
		12.f
	);

	FVector CurrentLoc = SpringArmComp->GetRelativeLocation();
	FVector TargetLoc = MinArmLocation;

	FVector NewLoc = FMath::VInterpTo(
		CurrentLoc,
		TargetLoc,
		DeltaTime,
		12.f
	);

	SpringArmComp->SetRelativeLocation(NewLoc);
}
void AFPCharacterBase::ZoomOut()
{
	if (!IsValid(SpringArmComp))
	{
		return;
	}
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	const float TargetLength = MaxArmLength;

	SpringArmComp->TargetArmLength = FMath::FInterpTo(
		SpringArmComp->TargetArmLength,
		TargetLength,
		DeltaTime,
		12.f
	);

	FVector CurrentLoc = SpringArmComp->GetRelativeLocation();
	FVector TargetLoc = MaxArmLocation;

	FVector NewLoc = FMath::VInterpTo(
		CurrentLoc,
		TargetLoc,
		DeltaTime,
		12.f
	);

	SpringArmComp->SetRelativeLocation(NewLoc);
}
