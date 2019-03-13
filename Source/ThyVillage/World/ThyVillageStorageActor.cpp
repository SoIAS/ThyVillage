// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillageStorageActor.h"
#include "Inventory/TheVillageInventoryComponent.h"
#include "Inventory/ThyVillageInventoryManager.h"
#include "ThyVillagePlayerController.h"

AThyVillageStorageActor::AThyVillageStorageActor()
{
	InventoryComponent = CreateDefaultSubobject<UTheVillageInventoryComponent>("Inventory Component");
	AddOwnedComponent(InventoryComponent);
}

void AThyVillageStorageActor::OnBeginInteraction_Implementation(AThyVillagePlayerController* PlayerController) const
{
	if (!PlayerController || !PlayerController->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller is invalid"));
		return;
	}

	PlayerController->GetInventoryManager()->SetStorageInventory(InventoryComponent);
	PlayerController->OpenInventory();
}

void AThyVillageStorageActor::OnEndInteraction_Implementation(AThyVillagePlayerController* PlayerController) const
{
	if (!PlayerController || !PlayerController->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller is invalid"));
		return;
	}

	PlayerController->CloseInventory();
	PlayerController->GetInventoryManager()->SetStorageInventory(nullptr);
}