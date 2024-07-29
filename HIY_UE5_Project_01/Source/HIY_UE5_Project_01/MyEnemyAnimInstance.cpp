// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAnimInstance.h"
#include "MyEnemy.h"

#include "Animation/AnimMontage.h"

UMyEnemyAnimInstance::UMyEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Animation/MyEnemyAnimMontage.MyEnemyAnimMontage'"));

	if (am.Succeeded())
	{
		_myAnimMontage = am.Object;
	}
}

void UMyEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// AMyEnemy* myEnemy = Cast<AMyEnemy>(TryGetPawnOwner());
	

}

void UMyEnemyAnimInstance::PlayDeadMontage()
{
	if (!Montage_IsPlaying(_myAnimMontage))
	{
		Montage_Play(_myAnimMontage);
	}
}

void UMyEnemyAnimInstance::AnimNotify_Dead()
{
	_deadDelegate.Broadcast();
}
