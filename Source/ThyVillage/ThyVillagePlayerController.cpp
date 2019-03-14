// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillagePlayerController.h"
#include "Inventory/ThyVillageInventoryManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "World/ThyVillageInteractableActor.h"

#include "DrawDebugHelpers.h"



AThyVillagePlayerController::AThyVillagePlayerController()
{
	InventoryManager = CreateDefaultSubobject<UThyVillageInventoryManager>("Inventory Manager");

	AddOwnedComponent(InventoryManager);
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
	
	FHitResult Hit{};
	if(!GetWorld()->LineTraceSingleByChannel(Hit, BeginTraceLocation, EndTraceLocation, ECollisionChannel::ECC_Visibility))
	{
		return;
	}

	if(auto HitInteractable = Cast<AThyVillageInteractableActor>(Hit.GetActor()))
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
