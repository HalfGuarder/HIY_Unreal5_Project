// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "MyInventoryComponent.generated.h"

class AMyCharacter;
class AMyItem;

DECLARE_MULTICAST_DELEGATE(InventoryOpenCloseDlgt);
DECLARE_MULTICAST_DELEGATE(PickUpItemDlgt);

DECLARE_MULTICAST_DELEGATE_TwoParams(ItemAddedDlgt, int32 itemId, int32 itemIndex);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HIY_UE5_PROJECT_01_API UMyInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ShowHideMouseCursor();

	void InvenOpenClose();

	void PrintItemList();

	void CheckItem(AMyItem* collisionItem) { _collisionItem = collisionItem; }
	void PickUpItem();
	void AddItem(AMyItem* item);
	void DropItem();

	bool CanSetWeapon();
	void GetWeapon(AMyItem* newWeapon);


public:
	UPROPERTY(VisibleAnyWhere, Category = Weapon)
	UStaticMeshComponent* _weapon;

	UPROPERTY(VisibleAnyWhere, Category = Weapon)
	AMyItem* _currentWeapon;

	UPROPERTY(VisibleAnyWhere, Category = Weapon)
	FName _weaponSocketRH = TEXT("hand_slide_r_Socket");

	InventoryOpenCloseDlgt _invenOpenCloseDlgt;
	PickUpItemDlgt _pickUpItemDlgt;
	ItemAddedDlgt _itemAddedDlgt;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = true))
	// class UUserWidget* _invenWidget;
	// class UWidgetComponent* _invenWidget;

	// Class
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = true))
	class UUserWidget* _invenWidgetUI;*/

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = true))
	TArray<AMyItem*> _myItems;

	bool _acceptPickUp = false;
	AMyItem* _collisionItem = nullptr;
};
