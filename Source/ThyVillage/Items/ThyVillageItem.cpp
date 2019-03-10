// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillageItem.h"

UThyVillageItem::UThyVillageItem() :
	MaxStackSize{ 1 }
{
	
}

FPrimaryAssetId UThyVillageItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId{ ItemType, GetFName() };
}