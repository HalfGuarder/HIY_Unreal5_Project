// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPet.h"
#include "MyPetAnimInstance.h"

// Sets default values
AMyPet::AMyPet()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> sm
	(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimalVarietyPack/Fox/Meshes/SK_Fox.SK_Fox'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation
	(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));


}

// Called when the game starts or when spawned
void AMyPet::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AMyPet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	checkDistance();

}

// Called to bind functionality to input
void AMyPet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMyPet::checkDistance()
{	
	//AMyCharacter* myCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	float distance = GetDistanceTo(_followMyChar);

	UE_LOG(LogTemp, Warning, TEXT("Distance : %f"), distance);

	return distance;
}

