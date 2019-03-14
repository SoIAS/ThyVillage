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
	constexpr int32 TraceLength = 5000;
	const auto BeginTraceLocation = PlayerCameraManager->GetCameraLocation();
	const auto EndTraceLocation = BeginTraceLocation + PlayerCameraManager->GetActorForwardVector() * TraceLength;

	// temp
	DrawDebugLine(GetWorld(), BeginTraceLocation, EndTraceLocation, FColor{ 255,0,0 }, true, 100, 0, 3);

	FHitResult HitResult{};
	if (!GetWorld()->LineTraceSingleByChannel(HitResult, BeginTraceLocation, EndTraceLocation, ECollisionChannel::ECC_Visibility))
	{
		return;
	}

	if (const auto HitInteractable = Cast<AThyVillageInteractableActor>(HitResult.GetActor()))
	{
		if (HitInteractable->IsWithinMinimumDistance(this))
		{
			HitInteractable->BeginInteraction(this);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("TOO FAR AWAY"));
		}
	}
}

void AThyVillagePlayerController::OnBeginInteraction(AThyVillageInteractableActor* const InteractionObject)
{
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