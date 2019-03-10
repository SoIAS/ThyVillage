// Fill out your copyright notice in the Description page of Project Settings.

#include "TheVillageInventoryComponent.h"
#include "Items/ThyVillageItem.h"

int32 FInventoryItem::AddToStack(const int32 Amount)
{
	if(!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot add to stack whose item is nullptr."));
		return 0;
	}

	const int32 EmptySpaceInStack = Item->GetMaxStackSize() - StackSize;
	const int32 AddedAmount = FMath::Min(Amount, EmptySpaceInStack);

	StackSize += AddedAmount;

	return AddedAmount;
}

int32 FInventoryItem::RemoveFromStack(const int32 Amount)
{
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot add to stack whose item is nullptr."));
		return 0;
	}

	if(StackSize < Amount)
	{
		const int32 RemovedAmount = StackSize;
		
		StackSize = 0;
		Item = nullptr;

		return RemovedAmount;
	}

	StackSize -= Amount;
	if(StackSize == 0)
	{
		Item = nullptr;
	}

	return Amount;
}

UTheVillageInventoryComponent::UTheVillageInventoryComponent() :
	Size{ 16 }
{
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UTheVillageInventoryComponent::AddItem(UThyVillageItem* const Item, const int32 Amount)
{
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot add a nullptr item."));
		return 0;
	}

	if (Amount < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot add 0 or less items."));
		return 0;
	}

	int32 LeftToAdd{ Amount };
	if (Item->IsStackable())
	{
		// Fill any existing stacks of the @Item first
		for (auto& ComponentItem : Items)
		{
			if (ComponentItem.Item == Item)
			{
				LeftToAdd -= ComponentItem.AddToStack(LeftToAdd);
			}

			if (LeftToAdd == 0)
			{
				break;
			}
		}
	}

	// Add leftover by adding new stacks of the @Item
	if (LeftToAdd > 0)
	{
		for (auto& ComponentItem : Items)
		{
			if (!ComponentItem.Item)
			{
				ComponentItem.Item = Item;
				LeftToAdd -= ComponentItem.AddToStack(LeftToAdd);
			}

			if (LeftToAdd == 0)
			{
				break;
			}
		}
	}

	return Amount - LeftToAdd;
}

bool UTheVillageInventoryComponent::AddItemExact(UThyVillageItem* Item, int32 Amount)
{
	return true;
}

int32 UTheVillageInventoryComponent::RemoveItem(UThyVillageItem* Item, int32 Amount)
{
	return 0;
}

bool UTheVillageInventoryComponent::RemoveItemExact(UThyVillageItem* Item, int32 Amount)
{
	return true;
}

bool UTheVillageInventoryComponent::HasItem(UThyVillageItem* const Item, const int32 Amount) const
{
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find a nullptr item."));
		return false;
	}

	if (Amount < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find 0 or less items."));
		return false;
	}

	int64 FoundItemsCount{};
	for (const auto& ComponentItem : Items)
	{
		if (ComponentItem.Item == Item)
		{
			FoundItemsCount += ComponentItem.StackSize;
		}

		if (FoundItemsCount >= Amount)
		{
			return true;
		}
	}

	return false;
}

bool UTheVillageInventoryComponent::HasItemExact(UThyVillageItem* Item, const int32 Amount) const
{
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find a nullptr item."));
		return false;
	}

	// todo, should we allow 0 for exact?
	if (Amount < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find 0 or less items."));
		return false;
	}

	int64 FoundItemsCount{};
	for (const auto& ComponentItem : Items)
	{
		if (ComponentItem.Item == Item)
		{
			FoundItemsCount += ComponentItem.StackSize;
		}

		if(FoundItemsCount > Amount)
		{
			return false;
		}
	}

	return FoundItemsCount == Amount;
}

FInventoryItem UTheVillageInventoryComponent::GetItem(const int32 Index) const
{
	if(Index < 0 || Index >= Size)
	{
		return {};
	}

	return Items[Index];
}

void UTheVillageInventoryComponent::PostInitProperties()
{
	Super::PostInitProperties();

	if(Size <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory size is set to 0 or lesser"));
		return;
	}

	Items.SetNumZeroed(Size);
}
