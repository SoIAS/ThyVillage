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
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot add a nullptr item."));
		return false;
	}

	if (Amount < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot add 0 or less items."));
		return false;
	}

	auto ItemsCopy{ Items };
	if (Item->IsStackable())
	{
		// Fill any existing stacks of the @Item first
		for (auto& ComponentItem : ItemsCopy)
		{
			if (ComponentItem.Item == Item)
			{
				Amount -= ComponentItem.AddToStack(Amount);
			}

			if (Amount == 0)
			{
				break;
			}
		}
	}

	// Add leftover by adding new stacks of the @Item
	if (Amount > 0)
	{
		for (auto& ComponentItem : ItemsCopy)
		{
			if (!ComponentItem.Item)
			{
				ComponentItem.Item = Item;
				Amount -= ComponentItem.AddToStack(Amount);
			}

			if (Amount == 0)
			{
				break;
			}
		}
	}

	if(Amount == 0)
	{
		Items = std::move(ItemsCopy);
		return true;
	}

	return false;
}

int32 UTheVillageInventoryComponent::RemoveItem(UThyVillageItem* Item, const int32 Amount)
{
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot remove a nullptr item."));
		return 0;
	}

	// todo<?>, use 0 for remove all?
	if (Amount < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot remove 0 or less items."));
		return 0;
	}

	int32 LeftToRemove{ Amount };
	for (auto& ComponentItem : Items)
	{
		if (ComponentItem.Item == Item)
		{
			LeftToRemove -= ComponentItem.RemoveFromStack(LeftToRemove);
		}

		if (LeftToRemove == 0)
		{
			break;
		}
	}

	return Amount - LeftToRemove;
}

bool UTheVillageInventoryComponent::RemoveItemExact(UThyVillageItem* Item, int32 Amount)
{
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot remove a nullptr item."));
		return false;
	}

	// todo<?>, use 0 for remove all?
	if (Amount < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot remove 0 or less items."));
		return false;
	}

	auto ItemsCopy{ Items };
	for (auto& ComponentItem : ItemsCopy)
	{
		if (ComponentItem.Item == Item)
		{
			Amount -= ComponentItem.RemoveFromStack(Amount);
		}

		if (Amount == 0)
		{
			break;
		}
	}

	if(Amount == 0)
	{
		Items = std::move(ItemsCopy);
		return true;
	}

	return false;
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
		UE_LOG(LogTemp, Warning, TEXT("Cannot get item, invalid Index."));
		return {};
	}

	return Items[Index];
}

bool UTheVillageInventoryComponent::SwapItem(int32 Index1, int32 Index2)
{
	if (Index1 < 0 || Index1 >= Size)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot swap items, Index1 is invalid."));
		return false;
	}

	if (Index2 < 0 || Index2 >= Size)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot swap items, Index2 is invalid."));
		return false;
	}

	if (Index1 == Index2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot swap items, Index1 is the same as Index2."));
		return false;
	}

	auto& Item1 = Items[Index1];
	auto& Item2 = Items[Index2];
	if(Item1.Item == Item2.Item)
	{
		const int32 StacksMoved = Item2.AddToStack(Item1.StackSize);
		Item1.RemoveFromStack(StacksMoved);
	}
	else
	{
		Swap(Item1, Item2);
	}

	return true;
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
