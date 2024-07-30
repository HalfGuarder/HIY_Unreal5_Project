// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
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

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class AMyCharacter* _followMyChar;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float CheckDistance();

	void FollowMyCharacter();

	FollowCharDG _followCharDG;

	UPROPERTY()
	UClass* _myCharacterClass;
	AActor* _myChar;
};
