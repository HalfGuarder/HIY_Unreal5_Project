// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	RootComponent = _sm;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh
	(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_TableRound.SM_TableRound'"));

	if (mesh.Succeeded())
	{
		_sm->SetStaticMesh(mesh.Object);
	}

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPawn::Move(const FInputActionValue& value)
{
	FVector2D movementVector = value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), movementVector.Y);
		AddMovementInput(GetActorRightVector(), movementVector.X);
	}
}

void AMyPawn::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Delegate Funtionr => CallAble, CallBack Funtion

	//PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
	//PlayerInputComponent->BindAxis(TEXT("RightLeft"), this, &AMyPawn::RightLeft);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		// Moving
		EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyPawn::Move);

		// Looking
		EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyPawn::Look);
	}
}

void AMyPawn::UpDown(float value)
{
	if(abs(value) >= 0.01)
	{
		FVector forward = GetActorForwardVector();
		AddMovementInput(forward, value);
	}
}

void AMyPawn::RightLeft(float value)
{
	if (abs(value) >= 0.01)
	{
		FVector rightLeft = GetActorRightVector();
		AddMovementInput(rightLeft, value);
	}
}

