// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Interactable.h"
#include "Engine/LocalPlayer.h"
#include "UIComponentManager.h"
#include "Building/BuildingBase.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADungeonCharacter

ADungeonCharacter::ADungeonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	WidgetManager = CreateDefaultSubobject<UUIComponentManager>(TEXT("WidgetManager"));
	
	PrimaryActorTick.bCanEverTick = true;

}

//////////////////////////////////////////////////////////////////////////// Input

void ADungeonCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ADungeonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADungeonCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADungeonCharacter::Look);
		
		// BuildingUI
		EnhancedInputComponent->BindAction(OpenBuildingUIAction, ETriggerEvent::Started, this, &ADungeonCharacter::OpenBuildingUI);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ADungeonCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ADungeonCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ADungeonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult Hit;
	
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * 1000.0f;
	
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility
	);
	
	TargetBuilding = Hit.GetActor();
	
	if (IInteractable* Interactable = Cast<IInteractable>(TargetBuilding))
	{
		Interactable->Highlight();
	}
}

void ADungeonCharacter::OpenBuildingUI()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Open Building UI"));
	
	OnShowBuildingUI.Broadcast(TargetBuilding);
	
	if (TargetBuilding == nullptr)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Target Building is nullptr"));
		return;
	}
	
	if (WidgetManager == nullptr)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Widget Manager is nullptr"));
		return;
	}
	
	ABuildingBase* Building = Cast<ABuildingBase>(TargetBuilding);
	
	if (!Building) return;
	
	WidgetManager->ShowWidget(Building->GetWidgetClass());
}

int32 ADungeonCharacter::GetCoin()
{
	return Coin;
}

void ADungeonCharacter::AddCoin(int32 Amount)
{
	int32 TempCoin = Coin + Amount;
	if (TempCoin > MaxCoin)
	{
		Coin = MaxCoin;
	}
	else
	{
		Coin += Amount;
	}
	
}

