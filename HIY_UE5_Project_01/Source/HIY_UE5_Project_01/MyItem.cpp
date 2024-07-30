// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MyCharacter.h"

// Sets default values
AMyItem::AMyItem()
{
	PrimaryActorTick.bCanEverTick = false;
 	
	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> sm
	(TEXT("/Script/Engine.StaticMesh'/Game/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_GreatAxe.SM_GreatAxe'"));

	if (sm.Succeeded())
	{
		_meshComponent->SetStaticMesh(sm.Object);
	}
	
	_meshComponent->SetupAttachment(RootComponent);
	_trigger->SetupAttachment(_meshComponent);

	_meshComponent->SetCollisionProfileName(TEXT("MyItem"));
	_trigger->SetCollisionProfileName(TEXT("MyItem"));
	_trigger->SetSphereRadius(60.0f);

	
}

// Called when the game starts or when spawned
void AMyItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyItem::OnMyCharacterOverlap);

}

void AMyItem::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
	auto myCharacter = Cast<AMyCharacter>(OtherActor);

	if(myCharacter != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s Collision"), *myCharacter->GetName());

		myCharacter->SetWeapon(this);

		/*if (myCharacter->GetMesh()->DoesSocketExist(myCharacter->_weaponSocketName))
		{
			_meshComponent->AttachToComponent(myCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, myCharacter->_weaponSocketName);
		}*/
	}

	return;
}

void AMyItem::Init()
{
	this->SetActorHiddenInGame(false);
	this->SetActorEnableCollision(true);
}

void AMyItem::Disable()
{
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
}

// Called every frame
void AMyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

