// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "MyGameInstance.h"
#include "MyAnimInstance.h"

#include "MyUIManager.h"

#include "MyInventoryUI.h"
#include "MyItem.h"
#include "MyHpBar.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/DamageEvents.h"
#include "MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Button.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Skeletal Mesh
	static ConstructorHelpers::FObjectFinder <USkeletalMesh> sm
	(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonCrunch/Characters/Heroes/Crunch/Meshes/Crunch.Crunch'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}

	// GookRullSetting
	GetMesh()->SetRelativeLocationAndRotation
	(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Capsule <- SpringArm <- Camera
	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);
	_camera->SetRelativeRotation(FRotator(10.0f, 0.0f, 0.0f));

	_springArm->TargetArmLength = 480.0f;
	_springArm->SetRelativeLocation(FVector(-50.0f, 0.0f, 200.0f));
	_springArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// Stat
	_statCom = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat_Com"));

	_hpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_hpBarWidget->SetupAttachment(GetMesh());
	_hpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	_hpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 270.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> hpBar
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/MyHpBar_BP.MyHpBar_BP_C'"));
	if (hpBar.Succeeded())
	{
		_hpBarWidget->SetWidgetClass(hpBar.Class);
	}

	// Inventory
	_invenCom = CreateDefaultSubobject<UMyInventoryComponent>(TEXT("Inventory_Com"));

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();	

	Init();

	// inven Bind
	/*auto invenUI = UIManager->GetInvenUI();
	if (invenUI != nullptr)
	{
		_invenCom->_invenOpenCloseDlgt.AddUObject(invenUI, &UMyInventoryUI::InvenOpenClose);
		_invenCom->_itemAddedDlgt.AddUObject(invenUI, &UMyInventoryUI::SetItem);
		invenUI->Drop_Btn->OnClicked.AddDynamic(this, &AMyCharacter::DropItem);
	}*/
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	
	if (_animInstance->IsValidLowLevel())
	{
		_animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackEnded);
		_animInstance->_attackDelegate.AddUObject(this, &AMyCharacter::AttackHit);
	}
	
	_statCom->SetLevelAndInit(_level);
	
	// hpBar Bind
	_hpBarWidget->InitWidget();
	auto hpBar = Cast<UMyHpBar>(_hpBarWidget->GetUserWidgetObject());
	if (hpBar != nullptr)
	{
		_statCom->_hpChangedDelegate.AddUObject(hpBar, &UMyHpBar::SetHpBarValue);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
	
		// Jumping
		EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Started, this, &AMyCharacter::JumpA);
	
		// Attacking
		EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &AMyCharacter::AttackA);

		// InvenOpenClose
		EnhancedInputComponent->BindAction(_invenOpenCloseAction, ETriggerEvent::Started, this, &AMyCharacter::InvenOpenClose);
		
		// PickUpItem
		EnhancedInputComponent->BindAction(_pickUpItemAction, ETriggerEvent::Started, this, &AMyCharacter::PickUpItem);
	
		// DropItem
		// EnhancedInputComponent->BindAction(_dropItemAction, ETriggerEvent::Started, this, &AMyCharacter::InvenOpenClose);
	}
}

void AMyCharacter::Init()
{
	_statCom->Reset();
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// TODO :
	// _hp -= Damage
	// Print Attacker Name

	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	float damaged = _statCom->SetCurHp(-Damage);

	return damaged;
}

void AMyCharacter::OnAttackEnded(UAnimMontage* montage, bool bInterrupted)
{
	_isAttacking = false;
}

void AMyCharacter::AttackHit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 180.0f;
	float attackRadius = 50.0f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;

	FColor drawColor = FColor::Green;


	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		FDamageEvent damageEvent;
		hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), damageEvent, this->GetController(), this);
	}
	DrawDebugSphere(GetWorld(), center, attackRadius, 12, drawColor, false, 2.0f);

	
}

void AMyCharacter::SetAttackDamage(AActor* actor, int32 amount)
{
	// actor = what set attack damage
	_statCom->SetAttackDamage(amount);
}

void AMyCharacter::SetItem(int32 itemId, int32 index)
{
	// TODO : invenWidget
	// auto invenUI = Cast<UMyGameInstance>(GetGameInstance())->GetUIManager()->GetInvenUI();
	// invenUI->SetItem(itemId, index);
}

void AMyCharacter::Move(const FInputActionValue& value)
{
	FVector2D movementVector = value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		_vertical = movementVector.Y;
		_horizontal = movementVector.X;

		AddMovementInput(GetActorForwardVector(), movementVector.Y);
		AddMovementInput(GetActorRightVector(), movementVector.X);
	}
}

void AMyCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
	}
}

void AMyCharacter::JumpA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();
	
	if (isPressed)
	{
		ACharacter::Jump();
	}
}

void AMyCharacter::AttackA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _isAttacking == false && _animInstance != nullptr)
	{
		_animInstance->PlayAttackMontage();
		_isAttacking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		_animInstance->JumpToSection(_curAttackIndex);
	}
}

