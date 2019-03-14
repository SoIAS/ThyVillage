// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThyVillagePlayerController.generated.h"

class UThyVillageInventoryManager;

UCLASS()
class THYVILLAGE_API AThyVillagePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AThyVillagePlayerController();

protected:
	void PostInitializeComponents() override;

public:
	void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
	void ToggleInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
	void OpenInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
	void CloseInventory();

	void TryInteraction();

	FORCEINLINE UThyVillageInventoryManager* GetInventoryManager() const noexcept
	{
		return InventoryManager;
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
	TSubclassOf<UThyVillageInventoryManager> InventoryManagerClass;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	UThyVillageInventoryManager* InventoryManager;
};