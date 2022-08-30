// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpongebobAttacksComponent.generated.h"


UENUM(BlueprintType)
enum class ESpongeBobState : uint8
{
	Normal = 0			UMETA(DisplayName = "Normal"),
	SimpleAttack = 1	UMETA(DisplayName = "SimpleAttack"),
	ComingUp = 2		UMETA(DisplayName = "ComingUp"),
	ComingDown = 3		UMETA(DisplayName = "ComingDown")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPONGEBOB_API USpongebobAttacksComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpongebobAttacksComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void SimpleAttack();


	UFUNCTION(BlueprintCallable)
	void ActiveAttackCollision();

	UFUNCTION(BlueprintCallable)
	void DeactiveAttackCollision();

	void ComingUp();

	void Move();


	bool bIsComingUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	ESpongeBobState State;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class ASpongebobCharacter* Spongebob;

	
};
