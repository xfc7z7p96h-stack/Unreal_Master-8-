// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "Components/SphereComponent.h"
#include "OffensiveBuilding.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class DUNGEON_API AOffensiveBuilding : public ABuildingBase
{
	GENERATED_BODY()
	
	float Radius = 1400.f;
	int32 Damage = 50;
	
public:
	AOffensiveBuilding();
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* FindComponent;
	
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* FireFX;
	
	virtual void Tick( float DeltaSeconds ) override;
	
	void FindEnemy();
	
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginPlay() override;
	
	FTimerHandle FindTimerHandle;
	
	
};
