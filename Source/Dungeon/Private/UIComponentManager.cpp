// Fill out your copyright notice in the Description page of Project Settings.


#include "UIComponentManager.h"

#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UUIComponentManager::UUIComponentManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUIComponentManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUIComponentManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUIComponentManager::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	if (CurrentWidget)
	{
		HideWidget();
	}
	
	APlayerController* PC = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
	if (!PC) return;
	
	CurrentWidget = CreateWidget<UUserWidget>(PC, WidgetClass);
	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport();
		
		PC->SetShowMouseCursor(true);
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(CurrentWidget->TakeWidget());
		PC->SetInputMode(InputMode);
	}
}

void UUIComponentManager::HideWidget()
{
	if (!CurrentWidget) return;
	
	APlayerController* PC = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
	
	CurrentWidget->RemoveFromViewport();
	CurrentWidget = nullptr;
	
	if (PC)
	{
		PC->SetShowMouseCursor(false);
		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}
}