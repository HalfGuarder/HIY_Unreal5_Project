// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "MyInventoryComponent.generated.h"

class AMyCharacter;
class AMyItem;

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

	void PrintItemList();

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


protected:
	UPROPERTY()
	AMyCharacter* _myCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = true))
	TArray<AMyItem*> _myItems;


};
