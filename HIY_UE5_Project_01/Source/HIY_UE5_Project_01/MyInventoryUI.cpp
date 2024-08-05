// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryUI.h"
#include "MyCharacter.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"

void UMyInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	auto array = Inven_UniformGrid->GetAllChildren();

	for (auto slot : array)
	{
		auto btn = Cast<UButton>(slot);
		if (btn)
		{
			_slotBtns.Add(btn);
			_slotBtnImages.Add(Cast<UImage>(btn->GetChildAt(0)));
		}
	}

	_axe = LoadObject<UTexture2D>
	(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/Icons/Tex_tools_01_b.Tex_tools_01_b'"));
	_default = LoadObject<UTexture2D>
	(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/Icons/Tex_default_slot.Tex_default_slot'"));

	Inven_Panel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMyInventoryUI::InvenOpenClose()
{
	if (_isOpen == true)
	{
		Inven_Panel->SetVisibility(ESlateVisibility::Collapsed);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		_isOpen = false;
		return;
	}
	else
	{
		Inven_Panel->SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		_isOpen = true;
		return;
	}
}

void UMyInventoryUI::SetItem(int32 itemId, int32 index)
{
	if(_slotBtnImages.IsEmpty() || !_slotBtnImages.IsValidIndex(index)) return;

	if (itemId == -1)
	{
		_slotBtnImages[index]->SetBrushFromTexture(_default);
	}
	else if (itemId == 1)
	{
		_slotBtnImages[index]->SetBrushFromTexture(_axe);
	}
	else
	{
		return;
	}
}
