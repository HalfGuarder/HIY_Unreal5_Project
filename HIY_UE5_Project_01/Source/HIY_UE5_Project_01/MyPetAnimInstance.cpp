// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPetAnimInstance.h"
#include "MyPet.h"

UMyPetAnimInstance::UMyPetAnimInstance()
{
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> am
	//(TEXT(""));
}

void UMyPetAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	AMyPet* myPet = Cast<AMyPet>(TryGetPawnOwner());
	if (myPet != nullptr)
	{
		_distance = myPet->checkDistance();
	}
}
