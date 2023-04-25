// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPC.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AMyPC::BeginPlay()
{
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem)
	{
		SubSystem->AddMappingContext(InputContext, 0);
	}
}
