// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpongebobPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPONGEBOB_API ASpongebobPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerHUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerHUD", meta = (AllowPrivateAccess = "true"))
	class UPlayerHUD* PlayerHUD;
};
