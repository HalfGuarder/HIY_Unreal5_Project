// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void AMyPlayerController::ShowMouseCursor()
{
	bShowMouseCursor = true;
}

void AMyPlayerController::HideMouseCursor()
{
	bShowMouseCursor = false;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (subsystem)
	{
		subsystem->AddMappingContext(_inputMappingContext, 0);
	}
}
