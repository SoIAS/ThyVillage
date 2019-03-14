// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillageInteractableActor.h"
#include "ThyVillagePlayerController.h"
#include "GameFramework/Pawn.h"

AThyVillageInteractableActor::AThyVillageInteractableActor()
{
	// Can be changed in derived classes
	PrimaryActorTick.bCanEverTick = false;

	MinimumDistance = 200;
	bIsInteractable = true;
}

void AThyVillageInteractableActor::BeginInteraction(AThyVillagePlayerController* PlayerController)
{
	if(!IsWithinMinimumDistance(PlayerController))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is not within mininmum distance to interactable object"));
		return;
	}

	PlayerController->OnBeginInteraction(this);
	OnBeginInteraction(PlayerController);
}

void AThyVillageInteractableActor::EndInteraction(AThyVillagePlayerController* PlayerController)
{
	OnEndInteraction(PlayerController);
	PlayerController->OnEndInteraction(this);
}

void AThyVillageInteractableActor::OnBeginInteraction_Implementation(AThyVillagePlayerController* PlayerController) const
{
}

void AThyVillageInteractableActor::OnEndInteraction_Implementation(AThyVillagePlayerController* PlayerController) const
{
}

bool AThyVillageInteractableActor::IsWithinMinimumDistance(AThyVillagePlayerController* const PlayerController) const
{
	if(!PlayerController || !PlayerController->IsValidLowLevel())
	{
		return false;
	}

	const auto* Pawn = PlayerController->GetPawn();
	
	return Pawn->GetDistanceTo(this) <= GetMinimumDistance();
}
