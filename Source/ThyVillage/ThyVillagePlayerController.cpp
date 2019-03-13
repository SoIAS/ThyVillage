// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillagePlayerController.h"
#include "Inventory/ThyVillageInventoryManager.h"


AThyVillagePlayerController::AThyVillagePlayerController()
{
	InventoryManager = CreateDefaultSubobject<UThyVillageInventoryManager>("Inventory Manager");

	AddOwnedComponent(InventoryManager);
}
