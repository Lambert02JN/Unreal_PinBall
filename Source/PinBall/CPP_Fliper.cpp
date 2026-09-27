// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Fliper.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_Fliper::ACPP_Fliper()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Flipper = CreateDefaultSubobject<UStaticMeshComponent>(FName("Fliper"));
	SetRootComponent(Flipper);
}

void ACPP_Fliper::BeginPlay()
{
	SetFlipper();
}

void ACPP_Fliper::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetFlipper();
}

void ACPP_Fliper::SetFlipper()
{
	if (FlipperType == EDirectionType::LEFT)
	{
		StartRotation = FRotator(0, -70, 0);
		EndRotation = FRotator(0, -120, 0);
	}
	else
	{
		StartRotation = FRotator(0, -110, 0);
		EndRotation = FRotator(0, -60, 0);
		Flipper->SetRelativeScale3D(FVector(-1, 1, 1));
	}
	Flipper->SetRelativeRotation(StartRotation);
}

void ACPP_Fliper::FlipperUp()
{
	auto sound = FlipperType == EDirectionType::LEFT ? FlipperLeft : FlipperRight;

	UGameplayStatics::SpawnSoundAttached(sound, Flipper);

	FLatentActionInfo latentInfo;
	latentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo(Flipper, Flipper->GetRelativeLocation(), EndRotation, false, false, 0.03f, false, EMoveComponentAction::Move, latentInfo);
	UE_LOG(LogTemp, Warning, TEXT("Controller_BackWard"));
}

void ACPP_Fliper::FlipperDown()
{
	auto sound = FlipperType == EDirectionType::LEFT ? FlipperLeft : FlipperRight;

	UGameplayStatics::SpawnSoundAttached(sound, Flipper);

	FLatentActionInfo latentInfo;
	latentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo(Flipper, Flipper->GetRelativeLocation(), StartRotation, false, false, 0.03f, false, EMoveComponentAction::Move, latentInfo);
}

