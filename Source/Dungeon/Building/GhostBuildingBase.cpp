// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostBuildingBase.h"

// Sets default values
AGhostBuildingBase::AGhostBuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;
	
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AGhostBuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhostBuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

