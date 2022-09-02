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
	bDoubleJump(false),
	bCanAttack(true)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SprinArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SprinArm->SetupAttachment(RootComponent);
	SprinArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SprinArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;


	BubbleWand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BubbleWand"));
	BubbleWand->SetupAttachment(GetMesh(), "BubbleWandSocket");
	BubbleWand->SetRelativeRotation(FRotator(0, 0, 90.f));
	BubbleWand->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
	BubbleWand->SetVisibility(false);

	BubbleHat = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BubbleHat"));
	BubbleHat->SetupAttachment(GetMesh());
	BubbleHat->SetVisibility(false);

	BubbleFootLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BubbleFootLeft"));
	BubbleFootLeft->SetupAttachment(GetMesh());
	BubbleFootLeft->SetVisibility(false);

	BubbleFootRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BubbleFootRight"));
	BubbleFootRight->SetupAttachment(GetMesh());
	BubbleFootRight->SetVisibility(false);

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
		if (GetSpongebobState() == ESpongeBobState::ComingUp)
		{
			GetAttackComponent()->State = ESpongeBobState::Normal;
			BubbleHat->SetVisibility(false);
			
		}
		
		
		bCanAttack = true;
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
	PlayerInputComponent->BindAction(FName("MovingDown"), IE_Pressed, this, &ASpongebobCharacter::MovingDown);

	PlayerInputComponent->BindAction(FName("TipTop"), IE_Pressed, this, &ASpongebobCharacter::TipTopPressed);
	PlayerInputComponent->BindAction(FName("TipTop"), IE_Released, this, &ASpongebobCharacter::TipTopReleased);
}

void ASpongebobCharacter::MoveForward(float Axis)
{
	if (Controller && Axis != 0 && (GetAttackComponent()->State == ESpongeBobState::Normal || GetAttackComponent()->
		State == ESpongeBobState::SimpleAttack))
	{
		const FRotator Yaw = FRotator(0, GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void ASpongebobCharacter::MoveRight(float Axis)
{
	if (Controller && Axis != 0 && (GetAttackComponent()->State == ESpongeBobState::Normal || GetAttackComponent()->
		State == ESpongeBobState::SimpleAttack))
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
	if (GetAttackComponent()->State == ESpongeBobState::Normal || GetAttackComponent()->State ==
		ESpongeBobState::SimpleAttack)
	{
		ACharacter::Jump();

		if (GetCharacterMovement()->IsFalling() && !bDoubleJump)
		{
			bDoubleJump = true;
			LaunchCharacter(FVector(0, 0, DoubleJumpForce), false, true);
		}
	}
}

void ASpongebobCharacter::Attack()
{
	if (GetAttackComponent()->State == ESpongeBobState::Normal && bCanAttack)
	{
		bCanAttack = false;
		GetAttackComponent()->SimpleAttack();
	}
}

void ASpongebobCharacter::MovingUp()
{
	GetAttackComponent()->ComingUp();
}

void ASpongebobCharacter::MovingDown()
{
	GetAttackComponent()->ComingDown();
}


void ASpongebobCharacter::TipTopPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = 100;
	bTipTop = true;
}

void ASpongebobCharacter::TipTopReleased()
{
	bTipTop = false;
	GetCharacterMovement()->MaxWalkSpeed = 400;
}
