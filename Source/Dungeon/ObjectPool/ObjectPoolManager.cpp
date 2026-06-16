// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"

#include "TestEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
AObjectPoolManager::AObjectPoolManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectPoolManager::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("AObjectPoolManager::BeginPlay"))
	SpawnMonsterPool();
}

// Called every frame
void AObjectPoolManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectPoolManager::SpawnMonsterPool()
{
	for (int32 i = 0; i <= SpawnMonsterAmount; i++ )
	{
		ATestEnemy* Enemy = GetWorld()->SpawnActor<ATestEnemy>(Monster);
		
		UE_LOG(LogTemp, Warning, TEXT("SpawnMonster"));
		
		Enemy->SetActorHiddenInGame(true);
		Enemy->SetActorEnableCollision(false);
		Enemy->SetActorTickEnabled(false);
		
		Enemy->bIsActive = false;
		
		Enemy->OnDeath.AddUniqueDynamic(this, &AObjectPoolManager::HandleDeath);
		
		MonsterPool.Add(Enemy);
	}
	for (AActor* Actor : MonsterPool)
	{
		UE_LOG(LogTemp, Warning, TEXT("Work"))
	}
}

FVector AObjectPoolManager::GetRandomLocation()
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!Character) return FVector::ZeroVector;
	
	FVector SpawnLocation = Character->GetActorLocation();
	SpawnLocation.X += FMath::RandRange(10, 100);
	
	return SpawnLocation;
	
}

ATestEnemy* AObjectPoolManager::GetObject()
{
	for (AActor* Actor : MonsterPool)
	{
		ATestEnemy* Enemy = Cast<ATestEnemy>(Actor);
		if (!Enemy) continue;
		
		if (!Enemy->bIsActive)
		{
			return Enemy;
		}
	}
	return nullptr;
}

void AObjectPoolManager::HandleDeath(ATestEnemy* Enemy)
{
	Enemy->SetActorHiddenInGame(true);
	Enemy->SetActorEnableCollision(false);
	Enemy->SetActorTickEnabled(false);
	
	Enemy->bIsActive = false;
}


