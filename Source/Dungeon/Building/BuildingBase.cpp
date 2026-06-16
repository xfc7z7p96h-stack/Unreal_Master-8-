// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"
#include "Dungeon/Widget/BuildingWidget.h"

// Sets default values
ABuildingBase::ABuildingBase()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	OutLineMesh = CreateDefaultSubobject<UStaticMeshComponent>("OutLineMesh");
	
 	RootComponent = StaticMesh;
	OutLineMesh->SetupAttachment(StaticMesh);
	OutLineMesh->SetVisibility(false);
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingBase::Highlight()
{
	UE_LOG(LogTemp, Warning, TEXT("Highlight Building"));
	OutLineMesh->SetVisibility(true);
	
	GetWorld()->GetTimerManager().SetTimer(
		OutLineTimer,
		this,
		&ABuildingBase::HighlightOff,
		0.1f,
		false
	);
}

void ABuildingBase::HighlightOff()
{
	OutLineMesh->SetVisibility(false);
	
	GetWorld()->GetTimerManager().ClearTimer(OutLineTimer);
}


void ABuildingBase::Interact()
{
	
}

TSubclassOf<UUserWidget> ABuildingBase::GetWidgetClass()
{
	return BuildingWidgetClass;
}

void ABuildingBase::DestroyedActor()
{
	Destroy();
}

