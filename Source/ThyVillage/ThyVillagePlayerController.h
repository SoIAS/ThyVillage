// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThyVillagePlayerController.generated.h"

class UThyVillageInventoryManager;
class AThyVillageInteractableActor;

UCLASS()
class THYVILLAGE_API AThyVillagePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AThyVillagePlayerController();

	void PlayerTick(float DeltaTime) override;

protected:
	void PostInitializeComponents() override;

public:
	void SetupInputComponent() override;

	/* Toggles inventory widget */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
	void ToggleInventory();

	/* Opens inventory widget */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
	void OpenInventory();

	/* Closes inventory widget */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = UI)
	void CloseInventory();

	/* Returns non owning ptr to inventory manager */
	FORCEINLINE UThyVillageInventoryManager* GetInventoryManager() const noexcept
	{
		return InventoryManager;
	}

protected:
	/* Inventory Manager Class to be instantiated */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
	TSubclassOf<UThyVillageInventoryManager> InventoryManagerClass;

	/* Instance of inventory manager */
	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	UThyVillageInventoryManager* InventoryManager;

public:
	/* */
	UFUNCTION(BlueprintImplementableEvent, Category = Interaction)
	void OnInteractionTooltip(bool bShow, AThyVillageInteractableActor* InteractableObjet);

	/* Tries to interact with object the player is looking at */
	void TryInteraction();

	/* Called when interaction begins */
	void OnBeginInteraction(AThyVillageInteractableActor* InteractionObject);
	
	/* Called when interaction ends */
	void OnEndInteraction(AThyVillageInteractableActor* InteractionObject);

protected:
	FHitResult GetInteractionHitResult() const;
	AThyVillageInteractableActor* GetInteractionHitActor() const;

private:
	/* Current object the player is interacting with */
	AThyVillageInteractableActor* CurrentlyInteractingWith;

	bool bInteractionTooltipShown;
};