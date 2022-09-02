// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/ProgressBar.h"


bool UPlayerHUD::Initialize()
{
	bool bSucces = Super::Initialize();
	if (!bSucces)
		return false;
	
	return bSucces;
}

void UPlayerHUD::SetHealth(float value)
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Green,FString::Printf(TEXT("HealthDeacrese")));
	HealthBar->SetPercent(value / 100);
}

