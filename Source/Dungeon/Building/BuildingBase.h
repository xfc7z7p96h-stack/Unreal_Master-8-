// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Interactable.h"
#include "BuildingBase.generated.h"

UCLASS()
class DUNGEON_API ABuildingBase : public AActor , public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componet")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componet")
	UStaticMeshComponent* OutLineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<class UBuildingWidget> BuildingWidgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FTimerHandle OutLineTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Highlight() override;
	virtual void HighlightOff() override;
	virtual void Interact() override;
	
	void DestroyedActor();
	
	TSubclassOf<UUserWidget> GetWidgetClass();

};
