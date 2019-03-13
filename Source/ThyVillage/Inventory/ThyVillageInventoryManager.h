// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThyVillageInventoryManager.generated.h"

class UTheVillageInventoryComponent;

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	PlayerInventory,
	StorageInventory
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THYVILLAGE_API UThyVillageInventoryManager : public UActorComponent
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

	/* Returns if player inventory can be used (can be implemented in blueprints)
	 * Returns true by default
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Inventory)
	bool CanPlayerUseInventory() const;

	/* Event called when player inventory changes (not the contents themselves though)*/
	UFUNCTION(BlueprintImplementableEvent)
	void PlayerInventoryChanged(UTheVillageInventoryComponent* NewPlayerInventory);

	/* Event called when storage inventory changes (not the contents themselves though)*/
	UFUNCTION(BlueprintImplementableEvent)
	void StorageInventoryChanged(UTheVillageInventoryComponent* NewStorageInventory);

	/* Swap items between inventories 
	 * Returns true if succeeded, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SwapItem(EInventoryType SourceInventoryType, int32 SourceIndex,
		EInventoryType DestinationInventoryType, int32 DestinationIndex);

	/* Returns inventory of inventory type or nullptr if one is not set */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	UTheVillageInventoryComponent* GetInventory(EInventoryType InventoryType) const;

protected:
	UPROPERTY(BlueprintReadOnly)
	UTheVillageInventoryComponent* PlayerInventory;

	UPROPERTY(BlueprintReadOnly)
	UTheVillageInventoryComponent* StorageInventory;
};
