// Fill out your copyright notice in the Description page of Project Settings.


#include "ShinyFlower.h"

// Sets default values
AShinyFlower::AShinyFlower() :
Style(EShinyStyleType::Normal)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AShinyFlower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShinyFlower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

