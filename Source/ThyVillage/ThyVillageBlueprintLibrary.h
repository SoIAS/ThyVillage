// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ThyVillageBlueprintLibrary.generated.h"

class AThyVillagePickupActor;
class UThyVillageItem;
class UThyVillageSingleton;

UCLASS()
class THYVILLAGE_API UThyVillageBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Pickup, meta = (WorldContext = "WorldContextObject"))
	static bool SpawnPickupActor(
		UObject* WorldContextObject,
		TSubclassOf<AThyVillagePickupActor> PickupActorClass,
		FVector Location,
		UThyVillageItem* Item,
		int32 Amount);

	static UThyVillageSingleton* GetThyVillageSingleton();
};
