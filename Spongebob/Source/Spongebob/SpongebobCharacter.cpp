// Fill out your copyright notice in the Description page of Project Settings.


#include "SpongebobCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpongebobAttacksComponent.h"
#include "SpongebobAttacksComponent.h"

// Sets default values
ASpongebobCharacter::ASpongebobCharacter() :
	TurnBase(45.f),
	bDoubleJump(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SprinArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SprinArm->SetupAttachment(RootComponent);
	SprinArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SprinArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	AttackComponent = CreateDefaultSubobject<USpongebobAttacksComponent>(TEXT("AttackComponent"));



	AutoPossessPlayer = EAutoReceiveInput::Player0;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 600.f, 0);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->FallingLateralFriction = 5.f;
	GetCharacterMovement()->AirControl = 3.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void ASpongebobCharacter::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void ASpongebobCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetCharacterMovement()->IsFalling())
	{
		if (bDoubleJump == true)
		{
			bDoubleJump = false;
		}

		GetAttackComponent()->State = ESpongeBobState::Normal;

	}


}

// Called to bind functionality to input
void ASpongebobCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASpongebobCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASpongebobCharacter::MoveRight);

	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ASpongebobCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("LookRight"), this, &ASpongebobCharacter::LookRight);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ASpongebobCharacter::Jump);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &ASpongebobCharacter::Attack);

	PlayerInputComponent->BindAction(FName("MovingUp"), IE_Pressed, this, &ASpongebobCharacter::MovingUp);
}

void ASpongebobCharacter::MoveForward(float Axis)
{
	if (Controller && Axis != 0 && (GetAttackComponent()->State == ESpongeBobState::Normal || GetAttackComponent()->State == ESpongeBobState::SimpleAttack))
	{
		const FRotator Yaw = FRotator(0, GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void ASpongebobCharacter::MoveRight(float Axis)
{
	if (Controller && Axis != 0 && (GetAttackComponent()->State == ESpongeBobState::Normal || GetAttackComponent()->State == ESpongeBobState::SimpleAttack))
	{
		const FRotator Yaw = FRotator(0, GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void ASpongebobCharacter::LookRight(float Axis)
{
	if (Controller && Axis != 0)
	{
		AddControllerYawInput(Axis * TurnBase * GetWorld()->GetDeltaSeconds());
	}
}

void ASpongebobCharacter::LookUp(float Axis)
{
	if (Controller && Axis != 0)
	{
		AddControllerPitchInput(Axis * TurnBase * GetWorld()->GetDeltaSeconds());
	}
}

void ASpongebobCharacter::Jump()
{
	ACharacter::Jump();

	if (GetCharacterMovement()->IsFalling() && !bDoubleJump)
	{
		bDoubleJump = true;
		LaunchCharacter(FVector(0, 0, DoubleJumpForce), false, true);
	}
}

void ASpongebobCharacter::Attack()
{
	if (GetAttackComponent()->State == ESpongeBobState::Normal)
	{
		GetAttackComponent()->SimpleAttack();
	}
}

void ASpongebobCharacter::MovingUp()
{
	GetAttackComponent()->ComingUp();
}
