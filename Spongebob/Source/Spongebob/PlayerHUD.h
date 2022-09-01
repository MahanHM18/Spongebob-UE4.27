// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPONGEBOB_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;

	
private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* Box = nullptr;

};
