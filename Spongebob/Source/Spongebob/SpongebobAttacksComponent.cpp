// Fill out your copyright notice in the Description page of Project Settings.


#include "SpongebobAttacksComponent.h"
#include "Components/BoxComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "SpongebobCharacter.h"

// Sets default values for this component's properties
USpongebobAttacksComponent::USpongebobAttacksComponent() :
	bIsComingUp(false),
	State(ESpongeBobState::Normal)

{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void USpongebobAttacksComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (Spongebob == nullptr)
	{
		Spongebob = Cast<ASpongebobCharacter>(GetOwner());
	}

}


// Called every frame
void USpongebobAttacksComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...


}

void USpongebobAttacksComponent::SimpleAttack()
{
	if (Spongebob)
	{
		State = ESpongeBobState::SimpleAttack;
		UAnimInstance* AnimInstance = Spongebob->GetMesh()->GetAnimInstance();

		if (AnimInstance)
		{
			AnimInstance->Montage_Play(AttackMontage);
		}

	}
}

void USpongebobAttacksComponent::ActiveAttackCollision()
{
	Spongebob->GetCharacterMovement()->RotationRate = FRotator(0, 0, 0);


	Spongebob->GetCharacterMovement()->GravityScale = .1;
	Spongebob->GetCharacterMovement()->StopMovementKeepPathing();

}

void USpongebobAttacksComponent::DeactiveAttackCollision()
{

	State = ESpongeBobState::Normal;
	Spongebob->GetCharacterMovement()->RotationRate = FRotator(0, 600.f, 0);
	Spongebob->GetCharacterMovement()->GravityScale = 1;
}

void USpongebobAttacksComponent::ComingUp()
{
	if (!Spongebob->GetDubleJump() && (State == ESpongeBobState::Normal || State == ESpongeBobState::SimpleAttack))
	{
		State = ESpongeBobState::ComingUp;
		Spongebob->LaunchCharacter(FVector(0, 0, 600), true, true);
		FTimerHandle Handle;
	}
}

void USpongebobAttacksComponent::Move()
{
}
