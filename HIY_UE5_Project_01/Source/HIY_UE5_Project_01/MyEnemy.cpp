// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "MyCharacter.generated.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder <USkeletalMesh> sm
	(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonHowitzer/Characters/Heroes/Howitzer/Meshes/HowitzerWasteland.HowitzerWasteland'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation
	(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	//for (int32 i = 1; i < 4; i++)
	//{
	int32 i = 1;
		FName name = FName(TEXT("Enemy %d"), i);
		FVector location = FVector(50 + (i * 100), 50 + (i * 100), 0);
		FRotator rot = FRotator(0, 0, 0);
		FActorSpawnParameters spawnParams;
		UWorld* world = GetWorld();

		AActor* enemy = world->SpawnActor(AMyEnemy::StaticClass(), &location, &rot);
	//}
}//name, location, rot, spawnParams

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

