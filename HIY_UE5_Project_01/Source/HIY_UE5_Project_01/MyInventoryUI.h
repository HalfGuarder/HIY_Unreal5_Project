// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyInventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class HIY_UE5_PROJECT_01_API UMyInventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void InvenOpenClose();

	UFUNCTION()
	void SetItem(int32 itemId, int32 index);

private:
	UPROPERTY(meta = (BindWidget)) // bind by name
	class UCanvasPanel* Inven_Panel;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* Inven_UniformGrid;
	
	UPROPERTY()
	bool _isOpen = false;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UButton*> _slotBtns;
	TArray<class UImage*> _slotBtnImages;
	class UTexture2D* _axe;
	class UTexture2D* _default;

	// DropBtn
	UPROPERTY(meta = (BindWidget))
	class UButton* Drop_Btn;
};