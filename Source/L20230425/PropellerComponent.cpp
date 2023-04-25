// Fill out your copyright notice in the Description page of Project Settings.


#include "PropellerComponent.h"

void UPropellerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AddLocalRotation(FRotator(0, 0, 3600.0f * DeltaTime));
}

UPropellerComponent::UPropellerComponent()
{
	ComponentTick
}
