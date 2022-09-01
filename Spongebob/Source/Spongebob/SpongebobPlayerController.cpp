// Fill out your copyright notice in the Description page of Project Settings.


#include "SpongebobPlayerController.h"

#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"

void ASpongebobPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerHUDClass)
	{
		PlayerHUD = Cast<UPlayerHUD>(CreateWidget(this,PlayerHUDClass));
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();

			PlayerHUD->SetHealth(34);
			
		}
	}
	
	
	
}
