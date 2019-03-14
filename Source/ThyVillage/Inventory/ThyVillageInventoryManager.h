// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThyVillageInventoryManager.generated.h"

class UTheVillageInventoryComponent;
class AThyVillagePlayerController;
class UThyVillageItem;

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	PlayerInventory,
	StorageInventory
};

UCLASS(Blueprintable)
class THYVILLAGE_API UThyVillageInventoryManager : public UObject
{
	GENERATED_BODY()

public:	
	UThyVillageInventoryManager();

	/* Sets the new Player inventory */
	UFUNCTION(BlueprintCallable, category = Inventory)
	void SetPlayerInventory(UTheVillageInventoryComponent* NewPlayerInventory);

	/* Sets the new Storage inventory */
	UFUNCTION(BlueprintCallable, category = Inventory)
	void SetStorageInventory(UTheVillageInventoryComponent* NewStorageInventory);

	/* Sets which player controller owns the inventory manager */
	void SetOwningPlayerController(AThyVillagePlayerController* PlayerController);

	/* Returns if player inventory can be used (can be implemented in blueprints)
	 * Returns true by default
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Inventory)
	bool CanPlayerUseInventory() const;

	/* Event called when player inventory changes (not the contents themselves though)*/
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void PlayerInventoryChanged(UTheVillageInventoryComponent* NewPlayerInventory);

	/* Event called when storage inventory changes (not the contents themselves though)*/
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void StorageInventoryChanged(UTheVillageInventoryComponent* NewStorageInventory);

	/* Swaps items between inventories 
	 * Returns true if succeeded, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SwapItem(EInventoryType SourceInventoryType, int32 SourceIndex,
		EInventoryType DestinationInventoryType, int32 DestinationIndex);

	/* Returns inventory of inventory type or nullptr if one is not set */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	UTheVillageInventoryComponent* GetInventory(EInventoryType InventoryType) const;

	void PickupItem(UThyVillageItem* Item, int32 Amount);

protected:
	/* Non owning pointer to existing player inventory */
	UPROPERTY(BlueprintReadOnly)
	UTheVillageInventoryComponent* PlayerInventory;

	/* Non owning pointer to some existing storage inventory */
	UPROPERTY(BlueprintReadOnly)
	UTheVillageInventoryComponent* StorageInventory;

	/* Pointer to player controller that owns this manager */
	UPROPERTY(BlueprintReadOnly)
	AThyVillagePlayerController* OwningPlayerController;
};