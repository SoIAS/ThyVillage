// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "World/ThyVillagePickupActor.h"
#include "ThyVillageSingleton.generated.h"


class AThyVillagePickupActor;

UCLASS(Blueprintable, BlueprintType)
class THYVILLAGE_API UThyVillageSingleton : public UObject
{
	GENERATED_BODY()

public:
	UThyVillageSingleton();

	FORCEINLINE TSubclassOf<AThyVillagePickupActor> GetPickupActorSubclass() const
	{
		return PickupActorClass;
	}

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Pickup Actor")
	TSubclassOf<AThyVillagePickupActor> PickupActorClass;

};
