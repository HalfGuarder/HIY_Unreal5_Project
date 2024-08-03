// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"

#include "MyCharacter.h"
#include "MyHpBar.h"
#include "MyGameInstance.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UMyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMyStatComponent::Reset()
{
	_curHp = _maxHp;
}

float UMyStatComponent::HpRatio()
{
	if (_maxHp == 0) return 0.0f;

	return _curHp / (float)_maxHp;
}

void UMyStatComponent::SetLevelAndInit(int32 level)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (myGameInstance != nullptr)
	{
		FMyStatData* data = myGameInstance->GetStatDataByLevel(level);
		_maxHp = data->maxHp;
		_attackDamage = data->attack;
		_curHp = _maxHp;

		GetOwner()->GetName();
		UE_LOG(LogTemp, Log, TEXT("%s... hp : %d, attackDamage : %d"), *GetOwner()->GetName(), _maxHp, _attackDamage);
	}
}

void UMyStatComponent::SetHp(int32 hp)
{
	// curHp modify only this function
	_curHp = hp;

	if (_curHp < 0) _curHp = 0;
	if (_curHp > _maxHp) _curHp = _maxHp;

	// auto owner = Cast<AMyCharacter>(GetOwner());
	// auto hpBar = owner->_hpBarWidget;

	float ratio = HpRatio();
	_hpChangedDelegate.Broadcast(ratio);
}

int32 UMyStatComponent::SetCurHp(float amount)
{
	int32 beforeHp = _curHp;

	// TODO
	// when amount damage income 
	// amount damage ~~> curHp
	int32 afterHp = beforeHp + amount;

	SetHp(afterHp);

	//if (_curHp < 0) _curHp = 0;

	//if (_curHp > _maxHp) _curHp = _maxHp;

	return beforeHp - afterHp;
}

void UMyStatComponent::SetAttackDamage(float amount)
{
	_attackDamage += amount;
}

