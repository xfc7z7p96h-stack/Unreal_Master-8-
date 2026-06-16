// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class AGhostBuildingBase;
class ABuildingBase;


/**
 * 
 */
UCLASS()
class DUNGEON_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
	bool bIsBuildMode = false;
	
	FHitResult Hit;
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_BuildMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_CurrentLocation;
	
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void CheckBuildMode();
	void UpdateBuildMode();
	void SpawnBuildingActor();
	

	
public:
	
	UPROPERTY(EditAnywhere, Category = "Building")
	TSubclassOf<AGhostBuildingBase> GhostBuildingClass;
	UPROPERTY()
	AGhostBuildingBase* GhostBuildingActor;
	
	UPROPERTY(EditAnywhere, Category = "Building")
	TSubclassOf<ABuildingBase> BuildingActor;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> BuildingModeWidgetClass;
	UPROPERTY()
	UUserWidget* BuildingModeWidget;
	
};
