// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPawn.h"
#include "MyCharacter.h"
#include "MyEnemy.h"
#include "MyPet.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<AMyCharacter> myCharacter
	(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/MyCharacter_BP.MyCharacter_BP_C'"));

	if (myCharacter.Succeeded())
	{
		DefaultPawnClass = myCharacter.Class;
	}

	static ConstructorHelpers::FClassFinder<AMyPet> myPet
	(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/MyPet_BP.MyPet_BP_C'"));
	if (myPet.Succeeded())
	{
		DefaultPawnClass = myCharacter.Class;
	}

	static ConstructorHelpers::FClassFinder<AMyEnemy> myEnemy
	(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/MyEnemy_BP.MyEnemy_BP_C'"));
	if (myEnemy.Succeeded())
	{
		_enemyClass = myEnemy.Class;
	}
}

void AMyGameModeBase::BeginPlay()
{
	FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() + FVector(1000.0f, 0.0f, 500.0f);
	FRotator rotator = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

	for (int32 i = 0; i < 3; i++)
	{
		location.X += 200.0 * i;
		location.Y += 200.0 * i;
		AMyEnemy* enemy = GetWorld()->SpawnActor<AMyEnemy>(_enemyClass, location, rotator);
		_enemies.Add(enemy);
	}
}
