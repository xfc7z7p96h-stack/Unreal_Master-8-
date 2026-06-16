// Fill out your copyright notice in the Description page of Project Settings.


#include "CommercialBuilding.h"

void ACommercialBuilding::CreateCoin()
{
	GetWorld()->GetTimerManager().SetTimer(
		AddCoinTimerHandle,
		[this]()
		{
			if (IsValid(this))
			{
				OnAddCoin.ExecuteIfBound(CoinAmount);
			}
		},
		CreateTime,
		false,
		CreateTime
	);
	
}

void ACommercialBuilding::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(AddCoinTimerHandle);
	
	Super::EndPlay(EndPlayReason);
}
