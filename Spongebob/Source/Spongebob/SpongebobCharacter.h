// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpongebobAttacksComponent.h"
#include "SpongebobCharacter.generated.h"

UCLASS()
class SPONGEBOB_API ASpongebobCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpongebobCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void MoveForward(float Axis);
	void MoveRight(float Axis);

	void LookRight(float Axis);
	void LookUp(float Axis);

	void Jump();

	void Attack();

	void MovingUp();

	void MovingDown();

	void TipTopPressed();
	void TipTopReleased();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SprinArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BubbleMeshs", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BubbleWand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BubbleMeshs", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BubbleHat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BubbleMeshs", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BubbleFootRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BubbleMeshs", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BubbleFootLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float DoubleJumpForce;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class USpongebobAttacksComponent* AttackComponent;


	float TurnBase;

	bool bDoubleJump;
	
	bool bCanAttack;
	

public:
	FORCEINLINE bool GetDubleJump() const { return bDoubleJump; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE USpongebobAttacksComponent* GetAttackComponent() { return AttackComponent; }

	FORCEINLINE ESpongeBobState GetSpongebobState() { return AttackComponent->State; }

	FORCEINLINE UStaticMeshComponent* GetBubbleWand() { return BubbleWand; }
	FORCEINLINE UStaticMeshComponent* GetBubbleHat() { return BubbleHat; }

	FORCEINLINE UStaticMeshComponent* GetBubbleFootR() { return BubbleFootRight; }
	FORCEINLINE UStaticMeshComponent* GetBubbleFootL() { return BubbleFootLeft; }

	bool bTipTop;
};
