// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillageBlueprintLibrary.h"
#include "World/ThyVillagePickupActor.h"
#include "Items/ThyVillageItem.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "ThyVillageSingleton.h"

bool UThyVillageBlueprintLibrary::SpawnPickupActor(
	UObject* WorldContextObject,
	TSubclassOf<AThyVillagePickupActor> PickupActorClass,
	FVector Location,
	UThyVillageItem* Item,
	int32 Amount)
{
	const FTransform Transform{ Location };

	const auto PickupActor = WorldContextObject->GetWorld()->SpawnActorDeferred<AThyVillagePickupActor>(PickupActorClass, Transform);
	if(!PickupActor->SetPickupItem(Item, Amount))
	{
		PickupActor->Destroy();
		return false;
	}
	
	UGameplayStatics::FinishSpawningActor(PickupActor, Transform);

	return true;
}

UThyVillageSingleton* UThyVillageBlueprintLibrary::GetThyVillageSingleton()
{
	const auto ThyVillageSingleton = Cast<UThyVillageSingleton>(GEngine->GameSingleton);
	if (!ThyVillageSingleton || !ThyVillageSingleton->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get ThyVillageSingleton"));
		return nullptr;
	}

	return ThyVillageSingleton;
}
