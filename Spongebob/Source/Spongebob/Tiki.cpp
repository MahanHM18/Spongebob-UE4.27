// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiki.h"

#include <string>

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATiki::ATiki()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ATiki::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATiki::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TargetVector = UGameplayStatics::GetPlayerCharacter(this,0)->GetActorLocation();
	FVector TikiVector = GetActorLocation();
	
	if (FVector::Dist(TargetVector,TikiVector) > 109)
	{
		FVector FixedTarget = FVector(TargetVector.X, TargetVector.Y, TikiVector.Z);
		FRotator TargetRotator = FVector(FixedTarget - TikiVector).Rotation() - FRotator(0, 90, 0);
		SetActorRotation(FMath::Lerp(GetActorRotation(),TargetRotator,6 * GetWorld()->GetDeltaSeconds()));
	}
	

	
	

}

