// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyStatComponent.h"

#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HIY_UE5_PROJECT_01_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	virtual void Init() override;

	FMyStatData* GetStatDataByLevel(int32 level);

private:
	UPROPERTY()
	class UDataTable* _statTable;

};
