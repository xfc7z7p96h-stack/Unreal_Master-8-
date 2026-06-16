// Fill out your copyright notice in the Description page of Project Settings.


#include "OffensiveBuilding.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TestEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Dataflow/DataflowAnyType.h"

AOffensiveBuilding::AOffensiveBuilding()
{
	FindComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	FindComponent->SetupAttachment(StaticMesh);
	
	PrimaryActorTick.bCanEverTick = true;
}

void AOffensiveBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(
		FindTimerHandle,
		this,
		&AOffensiveBuilding::FindEnemy,
		5.f,
		true,
		5.f
	);
}

void AOffensiveBuilding::Tick( float DeltaTime )
{
	
}

void AOffensiveBuilding::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(FindTimerHandle);
	
	Super::EndPlay(EndPlayReason);
}

void AOffensiveBuilding::FindEnemy()
{
	
	TArray<AActor*> Enemies;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	
	
	
	UKismetSystemLibrary::SphereOverlapActors(
		this,
		GetActorLocation(),
		Radius,
		ObjectTypes,
		nullptr,
		IgnoreActors,
		Enemies
	);
	
	ATestEnemy* Enemy = Cast<ATestEnemy>(Enemies[0]);
	
	if (!Enemy) return;
	FVector Start = GetActorLocation();
	FVector Target = Enemy->GetActorLocation();
	
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		FireFX,
		Start,
		LookAtRotation
	);
	
	UE_LOG(LogTemp,Warning, TEXT("Find Working"))
}
