// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/ThyVillageInteractableActor.h"
#include "ThyVillageStorageActor.generated.h"

class UTheVillageInventoryComponent;

UCLASS()
class THYVILLAGE_API AThyVillageStorageActor : public AThyVillageInteractableActor
{
	GENERATED_BODY()

public:
	AThyVillageStorageActor();

	void OnBeginInteraction_Implementation(AThyVillagePlayerController* PlayerController) const override;
	void OnEndInteraction_Implementation(AThyVillagePlayerController* PlayerController) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UTheVillageInventoryComponent* InventoryComponent;
};
