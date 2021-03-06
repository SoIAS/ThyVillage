// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillageInventoryManager.h"
#include "TheVillageInventoryComponent.h"
#include "ThyVillagePlayerController.h"
#include "ThyVillageBlueprintLibrary.h"
#include "ThyVillageSingleton.h"

#include "Runtime/Engine/Classes/GameFramework/Pawn.h"

UThyVillageInventoryManager::UThyVillageInventoryManager()
{
	PlayerInventory = nullptr;
	StorageInventory = nullptr;
	OwningPlayerController = nullptr;
}

void UThyVillageInventoryManager::SetPlayerInventory(UTheVillageInventoryComponent* const NewPlayerInventory)
{
	PlayerInventory = NewPlayerInventory;
	PlayerInventoryChanged(PlayerInventory);
}

void UThyVillageInventoryManager::SetStorageInventory(UTheVillageInventoryComponent* const NewStorageInventory)
{
	StorageInventory = NewStorageInventory;
	StorageInventoryChanged(StorageInventory);
}

void UThyVillageInventoryManager::SetOwningPlayerController(AThyVillagePlayerController* PlayerController)
{
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Settings owning player controller to invalid object"));
	}

	OwningPlayerController = PlayerController;
}

bool UThyVillageInventoryManager::SwapItem(const EInventoryType SourceInventoryType, const int32 SourceIndex,
	const EInventoryType DestinationInventoryType, const int32 DestinationIndex)
{
	if (!GetInventory(SourceInventoryType))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot swap items, source inventory is null"));
		return false;
	}

	if (!GetInventory(DestinationInventoryType))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot swap items, destination inventory is null"));
		return false;
	}

	bool Result{ true };
	if (GetInventory(SourceInventoryType) == GetInventory(DestinationInventoryType))
	{
		if (SourceIndex == DestinationIndex)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot swap item with itself"));
			return false;
		}

		Result = GetInventory(SourceInventoryType)->SwapItem(SourceIndex, DestinationIndex);
	}
	else
	{
		// todo, get references to both items and just do a swap (instead of adding/removing) ?
		const auto SourceItem = GetInventory(SourceInventoryType)->RemoveItemAt(SourceIndex);
		const auto DestinationItem = GetInventory(DestinationInventoryType)->RemoveItemAt(DestinationIndex);

		if (DestinationItem.Item && DestinationItem.StackSize > 0 &&
			!GetInventory(SourceInventoryType)->AddItemAt(SourceIndex, DestinationItem.Item, DestinationItem.StackSize))
		{
			UE_LOG(LogTemp, Error, TEXT("Something happend, cannot swap item to srouce inventory"));
			Result = false;
		}

		if (SourceItem.Item && SourceItem.StackSize > 0 &&
			!GetInventory(DestinationInventoryType)->AddItemAt(DestinationIndex, SourceItem.Item, SourceItem.StackSize))
		{
			UE_LOG(LogTemp, Error, TEXT("Something happend, cannot swap item to destination inventory"));
			Result = false;
		}
	}

	return Result;
}

UTheVillageInventoryComponent* UThyVillageInventoryManager::GetInventory(EInventoryType InventoryType) const
{
	switch (InventoryType)
	{
	case EInventoryType::PlayerInventory:
		return PlayerInventory;

	case EInventoryType::StorageInventory:
		return StorageInventory;
	}

	UE_LOG(LogTemp, Error, TEXT("Invalid inventory type"));
	return nullptr;
}

bool UThyVillageInventoryManager::CanPlayerUseInventory_Implementation() const
{
	return true;
}

void UThyVillageInventoryManager::PickupItem(UThyVillageItem* const Item, int32 Amount)
{
	if(!Item || Amount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot pickup invalid item"));
		return;
	}

	const int32 AddedAmount = PlayerInventory->AddItem(Item, Amount);
	Amount -= AddedAmount;

	if(Amount > 0)
	{
		const auto ThyVillageSingleton = UThyVillageBlueprintLibrary::GetThyVillageSingleton();
		const auto DropLocation = OwningPlayerController->GetPawn()->GetActorLocation();

		UThyVillageBlueprintLibrary::SpawnPickupActor(
			OwningPlayerController,
			ThyVillageSingleton->GetPickupActorSubclass(),
			DropLocation,
			Item,
			Amount);
	}
}
