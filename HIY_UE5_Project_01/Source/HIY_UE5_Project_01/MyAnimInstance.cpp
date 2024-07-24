// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework\PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Important Patt			dynamic cast
	AMyCharacter* myCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	if (myCharacter != nullptr)
	{
		_speed = myCharacter->GetVelocity().Size();
		_isFalling = myCharacter->GetMovementComponent()->IsFalling();
		_isAttacking = myCharacter->isAttackingCheck;
	} // Use Falling?
}

void UMyAnimInstance::AnimNotify_AttackEndCheck()
{
	AMyCharacter* myCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	myCharacter->isAttackingCheck = false;
}
