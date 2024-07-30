// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyEnemyAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(DeadDelegate);
DECLARE_MULTICAST_DELEGATE(DeathDelegate);

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

	UFUNCTION()
	void AnimNotify_Death();

	DeadDelegate _deadDelegate;
	DeathDelegate _deathDelegate;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	class UAnimMontage* _myAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	bool _isDead;

};
