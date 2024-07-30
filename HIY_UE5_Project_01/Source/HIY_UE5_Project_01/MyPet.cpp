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

	static ConstructorHelpers::FClassFinder<AMyCharacter> myCharacter
	(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/MyCharacter_BP.MyCharacter_BP_C'"));
	
	if (myCharacter.Succeeded())
	{
		_myCharacterClass = myCharacter.Class;
		//_myChar = Cast<AActor>(_myCharacterClass);
	}
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
	
	FollowMyCharacter();
}

// Called to bind functionality to input
void AMyPet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMyPet::CheckDistance()
{	
	float distance = GetDistanceTo(_myChar);

	//UE_LOG(LogTemp, Warning, TEXT("Distance : %f"), distance);

	return distance;
}

void AMyPet::FollowMyCharacter()
{


}