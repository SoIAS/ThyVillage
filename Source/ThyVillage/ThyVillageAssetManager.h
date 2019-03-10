// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ThyVillageAssetManager.generated.h"

class UThyVillageItem;

UCLASS()
class THYVILLAGE_API UThyVillageAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static const FPrimaryAssetType EquipmentItemType;
	static const FPrimaryAssetType ResourceItemType;

	static UThyVillageAssetManager& Get();

	/* Synchronous item load, reference is not maintained, so will be GC'ed if not referenced by caller */
	UThyVillageItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId) const;
};
