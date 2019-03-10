// Fill out your copyright notice in the Description page of Project Settings.

#include "ThyVillageResourceItem.h"
#include "ThyVillageAssetManager.h"

UThyVillageResourceItem::UThyVillageResourceItem() :
	ResourceType{ EResourceType::Wood }
{
	ItemType = UThyVillageAssetManager::ResourceItemType;
}