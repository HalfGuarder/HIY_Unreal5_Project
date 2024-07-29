// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyEnemyAnimInstance.generated.h"

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

private:

};
