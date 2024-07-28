// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"

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
	_camera->SetRelativeRotation(FRotator(15.0f, 0.0f, 0.0f));

	_springArm->TargetArmLength = 550.0f;
	_springArm->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	_springArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	// whene montage end, _isAttack be false
	// Delegate
	animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackEnded);

	// animInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AMyCharacter::AttackHit);
	animInstance->_attackDelegate.AddUObject(this, &AMyCharacter::AttackHit);

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// _myDelegate1.ExecuteIfBound();
	
	// 1.
	// _myDelegate2.ExecuteIfBound(50, 30);

	// 2. 
	// auto myAnimI = GetMesh()->GetA
	// nimInstance();
	// Cast<UMyAnimInstance>(myAnimI)->DelegateTest2(50, 30);
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
	}
}

void AMyCharacter::OnAttackEnded(UAnimMontage* montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Error, TEXT("Attack End!!"));
	_isAttacking = false;
}

void AMyCharacter::AttackHit()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack!!"));
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

	if (isPressed && _isAttacking == false)
	{
		auto myAnimI = GetMesh()->GetAnimInstance();
		Cast<UMyAnimInstance>(myAnimI)->PlayAttackMontage();
		_isAttacking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		Cast<UMyAnimInstance>(myAnimI)->JumpToSection(_curAttackIndex);
	}
}

