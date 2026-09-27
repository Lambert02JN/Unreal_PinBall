// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PopBumper.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PointLightComponent.h"
#include "CPP_PinBall.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/TimelineComponent.h"

// Sets default values
ACPP_PopBumper::ACPP_PopBumper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BumperBase = CreateDefaultSubobject<UStaticMeshComponent>(FName("BumperBase"));
	SetRootComponent(BumperBase);

	BumperBottom = CreateDefaultSubobject<UStaticMeshComponent>(FName("BumperBottom"));
	BumperBottom->SetupAttachment(BumperBase);

	Collision = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision"));
	Collision->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Collision->SetRelativeLocation(FVector(0, 0, 60));
	Collision->SetCapsuleHalfHeight(200);
	Collision->SetCapsuleRadius(120);
	Collision->SetupAttachment(BumperBase);

	Light = CreateDefaultSubobject<UPointLightComponent>(FName("Light"));
	Light->SetRelativeLocation(FVector(0, 0, 70));
	Light->Intensity = 0;
	Light->CastShadows = false;
	Light->SetupAttachment(BumperBase);

}

// Called when the game starts or when spawned
void ACPP_PopBumper::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACPP_PopBumper::OnOverlapBegin);

	if (PopBumperCurve)
	{
		FOnTimelineFloat TimeLineCallBack;
		TimeLineCallBack.BindUFunction(this, FName("PopBumperPlay"));
		PopBumperTimeLine.AddInterpFloat(PopBumperCurve, TimeLineCallBack);
	}
}

void ACPP_PopBumper::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Ball = Cast<ACPP_PinBall>(OtherActor))
	{
		Bump(Ball);
		UGameplayStatics::SpawnSoundAttached(BumperSound, BumperBase);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Effect, BumperBase->GetComponentLocation());
		PopBumperTimeLine.PlayFromStart();
		OnHitPopBumper.Broadcast();
	}
}

void ACPP_PopBumper::Bump(ACPP_PinBall* Ball)
{
	auto NewVec = (Ball->GetActorLocation() - GetActorLocation()) * Power;

	Ball->GetMesh()->SetPhysicsLinearVelocity(NewVec);
}

void ACPP_PopBumper::PopBumperPlay(float Value)
{
	BumperBottom->SetRelativeLocation(FMath::Lerp(FVector::ZeroVector, FVector(0, 0, -70), Value));
	BumperBase->SetScalarParameterValueOnMaterials(FName("Emissive"), FMath::Lerp(0, 20, Value));
	Light->SetIntensity(FMath::Lerp(0, 8000, Value));
}

// Called every frame
void ACPP_PopBumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PopBumperTimeLine.TickTimeline(DeltaTime);
}

