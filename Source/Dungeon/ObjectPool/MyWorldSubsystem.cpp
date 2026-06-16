// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWorldSubsystem.h"

#include "MyGameModeBase.h"
#include "ObjectPoolManager.h"
#include "Dungeon/Public/TestEnemy.h"


void UMyWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	
	if (!GM) return;
	
	AObjectPoolManager* Manager = GetWorld()->SpawnActor<AObjectPoolManager>(GM->PoolManager);
	
	PoolManager = Manager;
	
	GetWorld()->GetTimerManager().SetTimer(
		SpawnMonsterTimer,
		this,
		&UMyWorldSubsystem::SpawnMonster,
		5.f,
		true,
		5.f
	);
}

void UMyWorldSubsystem::SpawnMonster()
{
	ATestEnemy* Enemy = PoolManager->GetObject();
	
	if (!Enemy) return;
	
	Enemy->SetActorLocation(PoolManager->GetRandomLocation());
	Enemy->SetActorHiddenInGame(false);
	Enemy->SetActorEnableCollision(true);
	Enemy->SetActorTickEnabled(true);
	
	Enemy->bIsActive = true;
}


