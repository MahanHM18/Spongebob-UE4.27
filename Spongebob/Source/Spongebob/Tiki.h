// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tiki.generated.h"

UCLASS()
class SPONGEBOB_API ATiki : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATiki();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	class USkeletalMeshComponent* Mesh;

	bool bDoOnce = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Break();

	

};
