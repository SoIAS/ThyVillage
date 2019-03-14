// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThyVillageInteractableActor.generated.h"

class AThyVillagePlayerController;

UCLASS()
class THYVILLAGE_API AThyVillageInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AThyVillageInteractableActor();

	UFUNCTION(BlueprintCallable, Category = Interactable)
	void BeginInteraction(AThyVillagePlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = Interactable)
	void EndInteraction(AThyVillagePlayerController* PlayerController);

	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
	void OnBeginInteraction(AThyVillagePlayerController* PlayerController) const;

	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
	void OnEndInteraction(AThyVillagePlayerController* PlayerController) const;

	FORCEINLINE float GetMinimumDistance() const
	{
		return MinimumDistance;
	}

	FORCEINLINE bool GetIsInteractable() const
	{
		return bIsInteractable;
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interactable)
	bool IsWithinMinimumDistance(AThyVillagePlayerController* PlayerController) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interactable)
	float MinimumDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interactable)
	bool bIsInteractable;
};
