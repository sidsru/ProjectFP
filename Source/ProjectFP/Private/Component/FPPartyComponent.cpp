// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/FPPartyComponent.h"

// Sets default values for this component's properties
UFPPartyComponent::UFPPartyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UFPPartyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UFPPartyComponent::CanSwapTo(int32 NewIndex) const
{
	return false;
}

void UFPPartyComponent::ExecuteSwap(int32 NewIndex)
{
}

void UFPPartyComponent::Server_RequestSwapCharacter_Implementation(int32 NewIndex)
{
}


// Called every frame
//void UFPPartyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

