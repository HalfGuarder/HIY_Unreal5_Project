// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyEnemyAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(DeadDelegate);

/**
 * 
 */
UCLASS()
class HIY_UE5_PROJECT_01_API UMyEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyEnemyAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayDeadMontage();

	UFUNCTION()
	void AnimNotify_Dead();

	DeadDelegate _deadDelegate;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	class UAnimMontage* _myAnimMontage;
};
