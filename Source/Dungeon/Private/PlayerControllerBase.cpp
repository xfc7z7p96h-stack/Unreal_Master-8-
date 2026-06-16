// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Dungeon/Building/BuildingBase.h"

#include "Dungeon/Building/GhostBuildingBase.h"

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EIC =
	   Cast<UEnhancedInputComponent>(InputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enhanced Input Component"));
		EIC->BindAction(IA_BuildMode, ETriggerEvent::Started, this, &APlayerControllerBase::CheckBuildMode);
		EIC->BindAction(IA_CurrentLocation, ETriggerEvent::Started, this, &APlayerControllerBase::SpawnBuildingActor);
	}
}

void APlayerControllerBase::CheckBuildMode()
{
	if (bIsBuildMode)
	{
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting BuildMode"));
		bIsBuildMode = true;
		GhostBuildingActor = GetWorld()->SpawnActor<AGhostBuildingBase>(GhostBuildingClass);
		BuildingModeWidget = CreateWidget<UUserWidget>(this, BuildingModeWidgetClass);
		if (!BuildingModeWidget) return;
		BuildingModeWidget->AddToViewport();
		
	}
}

void APlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsBuildMode == true)
	{
		UpdateBuildMode();
	}
}

void APlayerControllerBase::UpdateBuildMode()
{
	if (!GhostBuildingActor) return;
	
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	
	if (Hit.bBlockingHit)
	{
		GhostBuildingActor->SetActorLocation(Hit.Location);
	}
}

void APlayerControllerBase::SpawnBuildingActor()
{
	if (bIsBuildMode == false) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Spawning Building Actor"));
	
	bIsBuildMode = false;
	
	if (GhostBuildingActor)
	{
		GhostBuildingActor->Destroy();
		GhostBuildingActor = nullptr;
	}
	
	if (!BuildingActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Building Actor Empty"));
		return;
	}
	
	ABuildingBase* NewBuilding = GetWorld()->SpawnActor<ABuildingBase>(BuildingActor);
	NewBuilding->SetActorLocation(Hit.Location);
	if (BuildingModeWidget)
	{
		BuildingModeWidget->RemoveFromViewport();
	}
}
