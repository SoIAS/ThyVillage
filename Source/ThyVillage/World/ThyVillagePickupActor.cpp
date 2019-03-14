// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillagePickupActor.h"
#include "ThyVillageAssetManager.h"
#include "ThyVillagePlayerController.h"
#include "Inventory/ThyVillageInventoryManager.h"

AThyVillagePickupActor::AThyVillagePickupActor()
{
	PickupItem = {};
	bPickedUp = true;
}

void AThyVillagePickupActor::OnBeginInteraction_Implementation(AThyVillagePlayerController* const PlayerController)
{
	if (bPickedUp)
	{
		return;
	}

	PlayerController->GetInventoryManager()->PickupItem(PickupItem.Item, PickupItem.StackSize);
	PickupItem = {};

	EndInteraction(PlayerController);

	Destroy();
}

bool AThyVillagePickupActor::SetPickupItemByStruct(const FInventoryItem NewPickupItem)
{
	if (IsPendingKillPending())
	{
		return false;
	}

	if (!NewPickupItem.Item || NewPickupItem.StackSize <= 0)
	{
		return false;
	}

	PickupItem = NewPickupItem;
	OnSetPickupItem(PickupItem);

	bPickedUp = false;

	return true;
}

bool AThyVillagePickupActor::SetPickupItem(UThyVillageItem* const Item, const int32 Amount)
{
	if (IsPendingKillPending())
	{
		return false;
	}

	if (!Item || Amount <= 0)
	{
		return false;
	}

	PickupItem = FInventoryItem{ Item, Amount };
	OnSetPickupItem(PickupItem);

	bPickedUp = false;

	return true;
}