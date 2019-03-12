// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheVillageInventoryComponent.generated.h"

class UThyVillageItem;

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = Item)
	UThyVillageItem *Item{ nullptr };

	UPROPERTY(BlueprintReadOnly, Category = Item)
	int32 StackSize{};

	int32 AddToStack(int32 Amount);
	int32 RemoveFromStack(int32 Amount);
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THYVILLAGE_API UTheVillageInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTheVillageInventoryComponent();

	/* Adds as much @Item as there is space for (may not add every @Item)
	 * Returns amount of @Item added
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	int32 AddItem(UThyVillageItem *Item, int32 Amount = 1);

	/* Adds @Amount of @Item, if there is not enough space, no @Item is added
	 * Returns true if successful, false otherwise 
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool AddItemExact(UThyVillageItem *Item, int32 Amount = 1);

	/* Adds @Item at @Index
	 * Returns true if the @Item was added, false otherwise
	 * If the same @Item (type) is already at @Index, it's stack size will be increased by @Amount (if doesn't overflow MaxStack size)
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool AddItemAt(int32 Index, UThyVillageItem *Item, int32 Amount = 1);

	/* Removes as much @Item as there is (no more than @Amount)
	 * Returns amount of removed @Item
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	int32 RemoveItem(UThyVillageItem *Item, int32 Amount = 1);

	/* Removes exact @Amount of @Item, if there is not enough amount of @Item, no @item is removed
	 * Returns true if successful, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool RemoveItemExact(UThyVillageItem *Item, int32 Amount = 1);

	/* Returns item that was at @Index 
	 * Might return an empty FInventoryItem object if there was no item at @Index or if @Index is invalid
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	FInventoryItem RemoveItemAt(int32 Index);

	/* Returns true if inventory has at least @Amount of @Item*/
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool HasItem(UThyVillageItem *Item, int32 Amount = 1) const;

	/* Returns true if inventory has exact @Amount of @Item*/
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool HasItemExact(UThyVillageItem *Item, int32 Amount = 1) const;

	/* Returns true if there is valid item at @Index */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool HasItemAt(int32 Index);

	/* Returns a shallow copy of item at @Index, if @Index is invalid, returns an empty Item*/
	UFUNCTION(BlueprintCallable, Category = Inventory)
	FInventoryItem GetItem(int32 Index) const;

	/* Swaps items at @Index1 and @Index2 positions.
	 * If items at @Index1 and @Index2 are the same item (type), the function moves stacks from @Index1 to @Index2
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SwapItem(int32 Index1, int32 Index2);

	/* Returns count of @Item */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	int32 GetItemCount(UThyVillageItem* Item) const;

protected:
	void PostInitProperties() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory, meta = (ClampMin = 1))
	int32 Size;

	UPROPERTY()
	TArray<FInventoryItem> Items;
};
