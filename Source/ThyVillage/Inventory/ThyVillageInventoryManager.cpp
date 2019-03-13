// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillageInventoryManager.h"
#include "TheVillageInventoryComponent.h"

UThyVillageInventoryManager::UThyVillageInventoryManager()
{
	PrimaryComponentTick.bCanEverTick = false;

	PlayerInventory = nullptr;
	StorageInventory = nullptr;
}

void UThyVillageInventoryManager::SetPlayerInventory(UTheVillageInventoryComponent* const PlayerInventory)
{
	this->PlayerInventory = PlayerInventory;
	PlayerInventoryChanged(this->PlayerInventory);
}

bool UThyVillageInventoryManager::CanPlayerUseInventory_Implementation() const
{
	return true;
}