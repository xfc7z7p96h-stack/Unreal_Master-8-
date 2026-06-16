#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BuildingData.generated.h"

USTRUCT(BlueprintType)
struct FBuildingData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building")
	FName BuildingName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building")
	int32 Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building")
	FText BuildingDescription;
};
