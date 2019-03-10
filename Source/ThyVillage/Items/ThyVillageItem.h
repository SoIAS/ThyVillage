// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "ThyVillageItem.generated.h"

UCLASS(Abstract, BlueprintType)
class THYVILLAGE_API UThyVillageItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UThyVillageItem();

	FPrimaryAssetId GetPrimaryAssetId() const override;

	FORCEINLINE const FPrimaryAssetType& GetItemType() const noexcept
	{
		return ItemType;
	}

	FORCEINLINE const FText& GetItemName() const noexcept
	{
		return ItemName;
	}

	FORCEINLINE const FText& GetItemDescription() const noexcept
	{
		return ItemDescription;
	}

	FORCEINLINE const FSlateBrush& GetItemIcon() const noexcept
	{
		return ItemIcon;
	}

	FORCEINLINE int32 GetMaxStackSize() const noexcept
	{
		return MaxStackSize;
	}

	UFUNCTION(BlueprintCallable, Category = Inventory)
	FORCEINLINE bool IsStackable() const noexcept
	{
		return MaxStackSize > 1;
	}

protected:
	// TODO (it  is set to visibleanywhere, but its still editable in editor - check it)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	FSlateBrush ItemIcon;

	/* Item is not stackable if max stack size is set to 1 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory, meta = (ClampMin = 1))
	int32 MaxStackSize;

	// todo,consumable (is consumable, consumable effect)
	// maxinventoryCount?
};