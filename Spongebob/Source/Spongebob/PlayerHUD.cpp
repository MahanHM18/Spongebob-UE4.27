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
	HealthBar->SetPercent(value / 100);
}

