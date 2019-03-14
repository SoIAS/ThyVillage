// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/ThyVillageInteractableActor.h"
#include "Inventory/TheVillageInventoryComponent.h"
#include "ThyVillagePickupActor.generated.h"

class UThyVillageItem;

UCLASS()
class THYVILLAGE_API AThyVillagePickupActor : public AThyVillageInteractableActor
{
	GENERATED_BODY()

public:
	AThyVillagePickupActor();

	void OnBeginInteraction_Implementation(AThyVillagePlayerController* PlayerController) override;

	/* Sets new pickup item 
 	 * Returns true if pickup item was set
	 */
	UFUNCTION(BlueprintCallable, Category = Pickup)
	bool SetPickupItemByStruct(FInventoryItem NewPickupItem);

	/* Sets pickup item, @Amount can be bigger than maxstacksize(?), will be resolved during pickup
	 * Returns true if pickup item was set
	 */
	UFUNCTION(BlueprintCallable, Category = Pickup)
	bool SetPickupItem(UThyVillageItem* Item, int32 Amount);

	/* Called when a new pickup item is set */
	UFUNCTION(BlueprintImplementableEvent, Category = Pickup)
	void OnSetPickupItem(FInventoryItem PickupItem);

private:
	/* Pickup item, max stack size can be bigger<?> than max, will be resolved at pickup */
	UPROPERTY()
	FInventoryItem PickupItem;

	UPROPERTY()
	bool bPickedUp;
};
