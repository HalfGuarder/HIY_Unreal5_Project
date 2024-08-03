// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHpBar.generated.h"

/**
 * 
 */
UCLASS()
class HIY_UE5_PROJECT_01_API UMyHpBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHpBarValue(float ratio);

private:
	UPROPERTY(meta = (BindWidget)) // bind by name
	class UProgressBar* PB_Char_HpBar;
};
