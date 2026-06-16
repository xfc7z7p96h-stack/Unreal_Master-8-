// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolManager.generated.h"


UCLASS()
class DUNGEON_API AObjectPoolManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectPoolManager();
	
	TArray<AActor*> MonsterPool; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectPool")
	int32 SpawnMonsterAmount = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATestEnemy> Monster;
	
	void SpawnMonsterPool();
	FVector GetRandomLocation();
	
	UFUNCTION()
	void HandleDeath(ATestEnemy* Enemy);
	
	ATestEnemy* GetObject();

};
