// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "MyCharacter.generated.h"


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

	// Stats
	_curHp = 1000;
	_attackDamage = 100.0f;
}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	/*for (int32 i = 1; i < 4; i++)
	{
		FName name = FName(TEXT("Enemy %d"), i);
		FVector location = FVector(50 + (i * 200), 50 + (i * 200), 0);
		FRotator rot = FRotator(0, 0, 0);
		FActorSpawnParameters spawnParams;
		UWorld* world = GetWorld();

		AActor* enemy = world->SpawnActor(AMyEnemy::StaticClass(), &location, &rot);
	}*/
}//name, location, rot, spawnParams

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

	_curHp -= Damage;

	UE_LOG(LogTemp, Log, TEXT("Attacker = %s"), *DamageCauser->GetName());
	UE_LOG(LogTemp, Log, TEXT("Current Hp = %f"), _curHp);

	if (_curHp < 0) _curHp = 0;

	if (IsDead())
	{
		DeadA();
	}

	return Damage;
}

bool AMyEnemy::IsDead()
{
	if (_curHp == 0) return true;

	return false;
}

void AMyEnemy::DeadA()
{
	FString name = this->GetName();
	UE_LOG(LogTemp, Error, TEXT("%s is Dead..."), *name);

	this->Destroy();
}

