// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _sm;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_TableRound.SM_TableRound'"));

	if (mesh.Succeeded())
	{
		_sm->SetStaticMesh(mesh.Object);
	}

	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("BeginPlay"));
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Log, TEXT("Tick : %f"), DeltaTime);

	FRotator rot = FRotator(0.0f, 90.0f, 0.0f);
	AddActorWorldRotation(rot * _rotationSpeed * DeltaTime);

	// 1. Actor2가 공전할 때 Actor를 바라보며 공전
	// - Actor는 계속 자전

	FVector moveV = FVector(0.0f, _moveSpeed, 0.0f);
	// AddActorWorldOffset(moveV * DeltaTime);
	// 2. SetActorLocation()
	// 문제점?
	// AddActorLocalOffset(moveV * DeltaTime);

	// 3. Quaternion (사원수)
	// 사원수 회전에 대해서 조사해 보기
}

