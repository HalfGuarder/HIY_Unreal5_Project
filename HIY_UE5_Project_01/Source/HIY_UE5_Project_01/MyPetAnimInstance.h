// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyPetAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HIY_UE5_PROJECT_01_API UMyPetAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyPetAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float _distance;
};
