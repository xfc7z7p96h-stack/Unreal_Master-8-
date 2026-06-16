// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dungeon/Building/BuildingBase.h"
#include "CommercialBuilding.generated.h"

DECLARE_DELEGATE_OneParam(FOnAddCoinSignature, int32 CoinAmount);

UCLASS()
class DUNGEON_API ACommercialBuilding : public ABuildingBase
{
	GENERATED_BODY()
	
public:
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void CreateCoin();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CoinAmount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CreateTime = 1.f;
	
	FOnAddCoinSignature OnAddCoin;
	
protected:
	
	FTimerHandle AddCoinTimerHandle;
	
	
};
