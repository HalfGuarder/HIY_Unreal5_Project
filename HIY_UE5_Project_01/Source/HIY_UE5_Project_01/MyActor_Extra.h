// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor_Extra.generated.h"

UCLASS()
class HIY_UE5_PROJECT_01_API AMyActor_Extra : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor_Extra();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* _sm_extra;

	UPROPERTY(EditAnywhere, Category = "Transform Value")
	float _rotationSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Transform Value")
	float _moveSpeed = 600.0f;
};
