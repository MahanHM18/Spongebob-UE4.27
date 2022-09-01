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
	Spongebob = Cast<ASpongebobCharacter>(GetOwner());

	BubbleWandAttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BubbleWandAttackBox"));
	if (Spongebob)
		BubbleWandAttackBox->SetupAttachment(Spongebob->GetBubbleWand());
	// ...
}


// Called when the game starts
void USpongebobAttacksComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Spongebob = Cast<ASpongebobCharacter>(GetOwner());
	//BubbleWandAttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BubbleWandAttackBox->OnComponentBeginOverlap.AddDynamic(this, &USpongebobAttacksComponent::OnBubbleWandOverlapped);
}


// Called every frame
void USpongebobAttacksComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void USpongebobAttacksComponent::SimpleAttack()
{
	if (Spongebob)
	{
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
	if (Spongebob->GetCharacterMovement()->IsFalling())
	{
		Spongebob->GetCharacterMovement()->GravityScale = .1;
		Spongebob->GetCharacterMovement()->StopMovementKeepPathing();
	}
	Spongebob->GetBubbleWand()->SetVisibility(true);

	State = ESpongeBobState::SimpleAttack;
}

void USpongebobAttacksComponent::DeactiveAttackCollision()
{
	Spongebob->GetBubbleWand()->SetVisibility(false);
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
		Spongebob->GetBubbleHat()->SetVisibility(true);
	}
}

void USpongebobAttacksComponent::ComingDown()
{
	if (Spongebob->GetCharacterMovement()->IsFalling() && State == ESpongeBobState::Normal)
	{
		State = ESpongeBobState::ComingDown;
		Spongebob->GetCharacterMovement()->GravityScale = 0;
		Spongebob->GetCharacterMovement()->StopMovementImmediately();
	}
}

void USpongebobAttacksComponent::StartBubbleBounce()
{
	Spongebob->GetCharacterMovement()->GravityScale = 3;
	Spongebob->GetBubbleFootL()->SetVisibility(true);
	Spongebob->GetBubbleFootR()->SetVisibility(true);
	//TODO
}

void USpongebobAttacksComponent::EndComingDown()
{
	Spongebob->GetCharacterMovement()->GravityScale = 1;
	Spongebob->GetBubbleFootL()->SetVisibility(false);
	Spongebob->GetBubbleFootR()->SetVisibility(false);
	State = ESpongeBobState::Normal;
}

void USpongebobAttacksComponent::OnBubbleWandOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                        bool bFromSweep,
                                                        const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Tiki"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, FString::Printf(TEXT("TIKI")));
	}
	
}
