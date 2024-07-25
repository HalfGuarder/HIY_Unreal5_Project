// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPet.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UAnimMontage;

DECLARE_DELEGATE(FollowCharDG);

UCLASS()
class HIY_UE5_PROJECT_01_API AMyPet : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float checkDistance();

	FollowCharDG _followCharDG;
};
