// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "MyStatComponent.h"
#include "MyEnemyAnimInstance.h"
#include "MyItem.h"

#include "Math/UnrealMathUtility.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder <USkeletalMesh> sm
	(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonHowitzer/Characters/Heroes/Howitzer/Meshes/HowitzerWasteland.HowitzerWasteland'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation
	(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	// Stat
	_statCom = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));

	// Item
	static ConstructorHelpers::FClassFinder<AMyItem> myItem
	(TEXT("/Script/CoreUObject.Class'/Script/HIY_UE5_Project_01.MyItem'"));
	if (myItem.Succeeded())
	{
		_itemClass = myItem.Class;
	}
}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AMyEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_enemyAnimInstance = Cast<UMyEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	if (_enemyAnimInstance->IsValidLowLevel())
	{
		_enemyAnimInstance->_deadDelegate.AddUObject(this, &AMyEnemy::DeadA);
		_enemyAnimInstance->_deadDelegate.AddUObject(this, &AMyEnemy::SpawnItem);
	}

	_statCom->SetLevelAndInit(_level);
}


void AMyEnemy::Init()
{
	_statCom->Reset();

	// SetActorHiddenInGame(false);
	// SetActorEnableCollision(true);
	// PrimaryActorTick.bCanEverTick = true;
}

void AMyEnemy::Disable()
{
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	PrimaryActorTick.bCanEverTick = false;
	// SetActorTickEnable(false);
}

void AMyEnemy::SpawnItem()
{
	float ranAngle = FMath::FRandRange(0, PI * 2.0f);
	float X = cosf(ranAngle) * 150;
	float Y = sinf(ranAngle) * 150;

	FVector location = GetActorLocation() + FVector(X, Y, 0.0f);
	FRotator rotator = GetActorRotation();

	AMyItem* item = GetWorld()->SpawnActor<AMyItem>(_itemClass, location, rotator);
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMyEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	float damaged = _statCom->SetCurHp(-Damage);

	if (IsDead())
	{
		_enemyAnimInstance->PlayDeadMontage();
	}

	return Damage;
}

bool AMyEnemy::IsDead()
{
	if (GetCurHp() == 0) return true;

	return false;
}

void AMyEnemy::DeadA()
{
	// FString name = this->GetName();

	Disable();
}

