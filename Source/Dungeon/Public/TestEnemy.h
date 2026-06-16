// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDead, class ATestEnemy*, Enemy);

UCLASS()
class DUNGEON_API ATestEnemy : public AActor
{
	GENERATED_BODY()
	
	int32 Hp = 100;
	
public:	
	// Sets default values for this actor's properties
	ATestEnemy();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	int32 GetHp() const;
	
	bool bIsActive = false;
	
	UPROPERTY(BlueprintAssignable)
	FOnEnemyDead OnDeath;

};
