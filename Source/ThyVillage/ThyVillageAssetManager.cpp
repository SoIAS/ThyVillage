// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillageAssetManager.h"
#include "Engine/Engine.h"
#include "Items/ThyVillageItem.h"

const FPrimaryAssetType	UThyVillageAssetManager::EquipmentItemType = TEXT("Equipment");
const FPrimaryAssetType	UThyVillageAssetManager::ResourceItemType = TEXT("Resource");

UThyVillageAssetManager& UThyVillageAssetManager::Get()
{
	const auto AssetManager = Cast<UThyVillageAssetManager>(GEngine->AssetManager);
	if(!AssetManager)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be ThyVillageAssetManager!"));
	}

	return *AssetManager;
}

UThyVillageItem* UThyVillageAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId) const
{
	const auto ItemPath = GetPrimaryAssetPath(PrimaryAssetId);
	const auto LoadedItem = Cast<UThyVillageItem>(ItemPath.TryLoad());

	if(!LoadedItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}

	return LoadedItem;
}
