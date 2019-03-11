// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThyVillagePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THYVILLAGE_API AThyVillagePlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
	void ToggleInventory();
	
};
