// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ThyVillageItem.h"
#include "ThyVillageResourceItem.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	// some test types
	Wood,
	Firewood,
	Water,
	Stone,
	Iron
};

UCLASS()
class THYVILLAGE_API UThyVillageResourceItem : public UThyVillageItem
{
	GENERATED_BODY()

public:
	UThyVillageResourceItem();

	FORCEINLINE EResourceType GetResourceItemType() const noexcept
	{
		return ResourceType;
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ResourceItem)
	EResourceType ResourceType;

};
