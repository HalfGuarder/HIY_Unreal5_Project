// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "MyPet.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMyAIController::AMyAIController()
{

}

// Controller on Pawn
void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &AMyAIController::RandMove, 0.5f, true);

}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void AMyAIController::RandMove()
{
	auto currentPawn = GetPawn();

	if (!currentPawn->IsValidLowLevel()) return;

	auto naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (naviSystem == nullptr) return;

	FNavLocation randLocation;

	auto isPet = Cast<AMyPet>(currentPawn);
	if (isPet != nullptr)
	{
		if (naviSystem->GetRandomPointInNavigableRadius(currentPawn->GetActorLocation(), 500.0f, randLocation))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, isPet->FollowCharacter());
			return;
		}
	}

	if (naviSystem->GetRandomPointInNavigableRadius(currentPawn->GetActorLocation(), 500.0f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation.Location);
	}
}
