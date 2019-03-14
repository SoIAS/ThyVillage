// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillagePlayerController.h"
#include "Inventory/ThyVillageInventoryManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "World/ThyVillageInteractableActor.h"

#include "DrawDebugHelpers.h"

AThyVillagePlayerController::AThyVillagePlayerController()
{
	InventoryManager = nullptr;

	CurrentlyInteractingWith = nullptr;

	bInteractionTooltipShown = false;
}

void AThyVillagePlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (CurrentlyInteractingWith)
	{
		if (!CurrentlyInteractingWith->IsWithinMinimumDistance(this))
		{
			CurrentlyInteractingWith->EndInteraction(this);
		}
	}

	if (!CurrentlyInteractingWith)
	{
		if (const auto HitInteractable = GetInteractionHitActor())
		{
			// todo, chekc if it was saem actor as before?
			if (!bInteractionTooltipShown && HitInteractable->IsWithinMinimumDistance(this))
			{
				OnInteractionTooltip(true, HitInteractable);
				bInteractionTooltipShown = true;
			}
		}
		else if (bInteractionTooltipShown)
		{
			OnInteractionTooltip(false, HitInteractable);
			bInteractionTooltipShown = false;
		}
	}
}

void AThyVillagePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (InventoryManagerClass->IsValidLowLevel())
	{
		InventoryManager = NewObject<UThyVillageInventoryManager>(this, InventoryManagerClass);
		InventoryManager->SetOwningPlayerController(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory Manager Class is invalid"));
	}
}

void AThyVillagePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, this, &AThyVillagePlayerController::TryInteraction);
}

void AThyVillagePlayerController::TryInteraction()
{
	if (const auto HitInteractable = GetInteractionHitActor())
	{
		if (HitInteractable->IsWithinMinimumDistance(this))
		{
			HitInteractable->BeginInteraction(this);
		}
	}
}

void AThyVillagePlayerController::OnBeginInteraction(AThyVillageInteractableActor* const InteractionObject)
{
	// no need to show the interaction tooltip anymore
	OnInteractionTooltip(false, nullptr);
	bInteractionTooltipShown = false;

	if (CurrentlyInteractingWith == InteractionObject)
	{
		return;
	}

	if (CurrentlyInteractingWith)
	{
		CurrentlyInteractingWith->EndInteraction(this);
	}

	CurrentlyInteractingWith = InteractionObject;
}

void AThyVillagePlayerController::OnEndInteraction(AThyVillageInteractableActor* const InteractionObject)
{
	CurrentlyInteractingWith = nullptr;
}

FHitResult AThyVillagePlayerController::GetInteractionHitResult() const
{
	constexpr int32 TraceLength = 5000;
	const auto BeginTraceLocation = PlayerCameraManager->GetCameraLocation();
	const auto EndTraceLocation = BeginTraceLocation + PlayerCameraManager->GetActorForwardVector() * TraceLength;

	FHitResult HitResult{};
	GetWorld()->LineTraceSingleByChannel(HitResult, BeginTraceLocation, EndTraceLocation, ECollisionChannel::ECC_Visibility);

	return HitResult;
}

AThyVillageInteractableActor* AThyVillagePlayerController::GetInteractionHitActor() const
{
	const auto HitResult = GetInteractionHitResult();

	return Cast<AThyVillageInteractableActor>(HitResult.GetActor());
}
