// Fill out your copyright notice in the Description page of Project Settings.


#include "P38GameModeBase.h"

#include "MyPC.h"
#include "P38Pawn.h"

AP38GameModeBase::AP38GameModeBase()
{
	PlayerControllerClass = AMyPC::StaticClass();
	DefaultPawnClass = AP38Pawn::StaticClass();

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("진호 잡아와"));
}
