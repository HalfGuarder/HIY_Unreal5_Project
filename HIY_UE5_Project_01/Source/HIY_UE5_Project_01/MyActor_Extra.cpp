// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_Extra.h"
#include "Kismet\KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyActor_Extra::AMyActor_Extra()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sm_extra = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _sm_extra;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));

	if (mesh.Succeeded())
	{
		_sm_extra->SetStaticMesh(mesh.Object);
	}

	UE_LOG(LogTemp, Warning, TEXT("Constructor_Extra"));
}

// Called when the game starts or when spawned
void AMyActor_Extra::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("BeginPlay_Extra"));
	
}

// Called every frame
void AMyActor_Extra::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Log, TEXT("Tick : %f"), DeltaTime);

	if (GetAttachParentActor() != nullptr)
	{
		FVector parentV = GetAttachParentActor()->GetActorLocation();
		FVector myV = GetActorLocation();
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(myV, parentV);

		SetActorRotation(rot);
	}
	else
	{
		FRotator rot = FRotator(0.0f, 90.0f, 0.0f);
		AddActorWorldRotation(rot * _rotationSpeed * DeltaTime);
	}

	// 1. Actor2�� ������ �� Actor�� �ٶ󺸸� ����
	// - Actor�� ��� ����

	FVector moveV = FVector(0.0f, _moveSpeed, 0.0f);
	// AddActorWorldOffset(moveV * DeltaTime);
	// 2. SetActorLocation()
	// ������?
	// AddActorLocalOffset(moveV * DeltaTime);
	// �� �� �Ǵ��� ã��, SetActorLocation���� AddActorWorldOffsetó�� �����̰� �����
	

	// 3. Quaternion (�����)
	// ����� ȸ���� ���ؼ� ������ ����
}

