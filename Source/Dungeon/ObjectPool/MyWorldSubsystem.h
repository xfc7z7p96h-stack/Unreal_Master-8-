// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MyWorldSubsystem.generated.h"

class AObjectPoolManager;
/**
 * 
 */
UCLASS()
class DUNGEON_API UMyWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	AObjectPoolManager* PoolManager;
public:
	
	
	virtual void OnWorldBeginPlay(UWorld& InWorld);
	
	void SpawnMonster();
	
protected:
	
	FTimerHandle SpawnMonsterTimer;
	
};
