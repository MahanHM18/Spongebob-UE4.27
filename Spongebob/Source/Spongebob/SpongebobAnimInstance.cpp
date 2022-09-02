// Fill out your copyright notice in the Description page of Project Settings.


#include "SpongebobAnimInstance.h"
#include "SpongebobCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void USpongebobAnimInstance::NativeInitializeAnimation()
{
	if (Spongebob == nullptr)
	{
		Spongebob = Cast<ASpongebobCharacter>(TryGetPawnOwner());
	}
}

void USpongebobAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (Spongebob)
	{
		FVector Velocity = Spongebob->GetVelocity();

		Velocity.Z = 0;

		Speed = Velocity.Size();

		VerticalVelocity = Spongebob->GetVelocity().Z;

		bIsAir = Spongebob->GetCharacterMovement()->IsFalling();

		bDoubleJump = Spongebob->GetDubleJump();

		State = Spongebob->GetSpongebobState();

		bTipTop = Spongebob->bTipTop;
	}


}
