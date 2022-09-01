// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"

bool UPlayerHUD::Initialize()
{
	bool bSucces = Super::Initialize();
	if (!bSucces)
		return false;
	
	return bSucces;

	Cast<UImage>(Box->GetChildAt(0))->SetOpacity(0);
	
}
