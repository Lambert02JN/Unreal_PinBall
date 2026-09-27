// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PinBall.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Components/AudioComponent.h"

// Sets default values
ACPP_PinBall::ACPP_PinBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PinBall = CreateDefaultSubobject<UStaticMeshComponent>(FName("PinBall"));
	SetRootComponent(PinBall);
	PinBall->SetSimulatePhysics(true);
	PinBall->SetEnableGravity(false);
	PinBall->SetCollisionProfileName(FName("PhysicsActor"));
	PinBall->SetSimulatePhysics(true);
	PinBall->SetEnableGravity(false);

	Audio = CreateDefaultSubobject<UAudioComponent>(FName("Audio"));
	Audio->AttachTo(PinBall);

}

// Called when the game starts or when spawned
void ACPP_PinBall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPP_PinBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void ACPP_PinBall::Move(float DeltaTime)
{
	auto ImpulseX = Speed * DeltaTime * -1.0f;
	PinBall->AddImpulse(FVector(ImpulseX, 0, 0), "None", true);

	FHitResult HitResult;
	FVector End = GetActorLocation() - FVector(0, 0, 500);
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), End, ECollisionChannel::ECC_Visibility);

	if (IsHit)
	{
		auto Rebound = HitResult.ImpactNormal * -1.0f * Stickness * DeltaTime;
		PinBall->AddImpulse(Rebound, "None", true);
	}
}

void ACPP_PinBall::SetAudio()
{
	auto Volume = GetVelocity().Size() / 2000.0f;
	//SetVolume
	Audio->SetVolumeMultiplier(FMath::Clamp(Volume, 0.0f, 1.2f));
	//SetPitch
	Audio->SetPitchMultiplier(FMath::Clamp(Volume, 0.9f, 1.1f));
}




