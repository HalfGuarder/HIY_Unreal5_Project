// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryComponent.h"
#include "MyCharacter.h"
#include "MyItem.h"
#include "Math/UnrealMathUtility.h"
#include "Components/WidgetComponent.h"
#include "MyInventoryUI.h"

// Sets default values for this component's properties
UMyInventoryComponent::UMyInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UMyInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UMyInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMyInventoryComponent::ShowHideMouseCursor()
{
	// GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	// GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
}

void UMyInventoryComponent::InvenOpenClose()
{
	_invenOpenCloseDlgt.Broadcast();
}

void UMyInventoryComponent::PrintItemList()
{
	int32 itemIndex = _myItems.Num();

	GEngine->AddOnScreenDebugMessage(-1, 3.5f, FColor::Magenta, FString::Printf(TEXT("------------")));
	while (!(itemIndex <= 0))
	{
		FString itemName = _myItems[itemIndex - 1]->GetName();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.5f, FColor::Magenta, FString::Printf(TEXT("%s"), *itemName));
		}
		itemIndex--;
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.5f, FColor::Magenta, FString::Printf(TEXT("---Items---")));
}

void UMyInventoryComponent::PickUpItem()
{
	if (_collisionItem == nullptr) return;

	// _pickUpItemDelegate.Broadcast();
	_acceptPickUp = true;	
}

void UMyInventoryComponent::AddItem(AMyItem* item)
{
	_myItems.Add(item);
	_itemAddedDlgt.Broadcast(item->_itemId, _myItems.Num() - 1);

	PrintItemList();
}

void UMyInventoryComponent::DropItem()
{
	if (_myItems.Num() == 0) return;

	auto myCharacter = Cast<AMyCharacter>(GetOwner());
	AMyItem* targetItem = _myItems.Last();

	if (myCharacter != nullptr)
	{
		if (targetItem == _currentWeapon)
		{
			myCharacter->SetAttackDamage(_currentWeapon, -(_currentWeapon->_damage));
			_currentWeapon = nullptr;
		}
	}
	targetItem->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

	float ranAngle = FMath::FRandRange(0, PI * 2.0f);
	float X = cosf(ranAngle) * 300;
	float Y = sinf(ranAngle) * 300;

	FVector playerPos = GetOwner()->GetActorLocation();

	targetItem->SetItemPos(playerPos + FVector(X, Y, 0.0f));

	_myItems.Remove(targetItem);
	int32 itemsSize = _myItems.Num();
	myCharacter->SetItem(-1, itemsSize);
}

bool UMyInventoryComponent::CanSetWeapon()
{
	return (_currentWeapon == nullptr);
}

void UMyInventoryComponent::GetWeapon(AMyItem* newWeapon)
{
	if (_acceptPickUp == false) return;

	if (newWeapon != nullptr)
	{
		auto myCharacter = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		AddItem(newWeapon);
		newWeapon->SetActorEnableCollision(false);

		if (CanSetWeapon())
		{
			newWeapon->AttachToComponent(myCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, _weaponSocketRH);
			_currentWeapon = newWeapon;
			myCharacter->SetAttackDamage(newWeapon, newWeapon->_damage);
		}
		else
		{
			newWeapon->SetActorHiddenInGame(true);
			newWeapon->AttachToComponent(myCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}

		newWeapon->SetOwner(myCharacter);

		_acceptPickUp = false;
	}

}

