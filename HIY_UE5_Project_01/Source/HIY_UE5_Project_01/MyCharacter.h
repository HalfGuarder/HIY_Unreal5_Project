// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyStatComponent.h"
#include "MyInventoryComponent.h"

#include "MyCharacter.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UAnimMontage;
class AMyItem;

UCLASS()
class HIY_UE5_PROJECT_01_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void Init();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnAttackEnded(UAnimMontage* montage, bool bInterrupted);

	UFUNCTION()
	void AttackHit();

	// Stats
	int32 GetCurHp() { return _statCom->GetCurHp(); }
	void SetAttackDamage(AActor* actor, int32 amount);

	// Inventory
	void InvenOpenClose() { _invenCom->InvenOpenClose(); }
	void CheckItem(AMyItem* collisionItem) { _invenCom->CheckItem(collisionItem); }
	void PickUpItem() { _invenCom->PickUpItem(); }
	void AddItem(AMyItem* item) { _invenCom->AddItem(item); }
	void DropItem() { _invenCom->DropItem(); }

	bool CanSetWeapon() { return _invenCom->CanSetWeapon(); }
	void GetWeapon(AMyItem* newWeapon) { _invenCom->GetWeapon(newWeapon); }

protected:
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void JumpA(const FInputActionValue& value);
	void AttackA(const FInputActionValue& value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	class UInputAction* _moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	class UInputAction* _lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	class UInputAction* _jumpAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = true))
	UAnimMontage* _attackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	class UInputAction* _attackAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	bool _isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	int32 _curAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	float _vertical = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	float _horizontal = 0.0f;

	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = true))
	class USpringArmComponent* _springArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = true))
	class UCameraComponent* _camera;

	// Animation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = true))
	class UMyAnimInstance* _animInstance;

	// Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _level = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	class UMyStatComponent* _statCom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* _hpBarWidget;

	// Inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inven, meta = (AllowPrivateAccess = true))
	class UMyInventoryComponent* _invenCom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inven, meta = (AllowPrivateAccess = true))
	class UUserWidget* _invenWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	class UInputAction* _invenOpenCloseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	class UInputAction* _pickUpItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	class UInputAction* _dropItemAction;
private:

};
