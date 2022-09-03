// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShinyFlower.generated.h"

UENUM(BlueprintType)
enum class EShinyStyleType : uint8
{
	Normal = 0 UMETA(DisplayName = "Normal"),
	FromBox = 1 UMETA(DisplayName = "FromBox"),
};

UCLASS()
class SPONGEBOB_API AShinyFlower : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShinyFlower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "StyleType",meta = (AllowPrivateAccess = "true"))
	EShinyStyleType Style;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;
};
