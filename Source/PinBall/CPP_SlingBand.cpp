// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SlingBand.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "CPP_PinBall.h"
#include "Components/TimelineComponent.h"

// Sets default values
ACPP_SlingBand::ACPP_SlingBand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SlingBand = CreateDefaultSubobject<UStaticMeshComponent>(FName("SlingBand"));
	SlingBand->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

	Collision = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision"));
	Collision->SetCollisionProfileName(FName("OverlapAllDynamic"));

	SetRootComponent(SlingBand);
	Collision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACPP_SlingBand::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACPP_SlingBand::OnOverlapBegin);

	if (SlingBandCurve)
	{
		FOnTimelineFloat TimeLineCallBack;
		TimeLineCallBack.BindUFunction(this, FName("SlingBandPlay"));
		SlingBandTimeLine.AddInterpFloat(SlingBandCurve, TimeLineCallBack);
	}
}

void ACPP_SlingBand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SlingBandTimeLine.TickTimeline(DeltaTime);
}

void ACPP_SlingBand::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Ball = Cast<ACPP_PinBall>(OtherActor))
	{
		auto Move = Collision->GetForwardVector() * 2500.f;
		Ball->GetMesh()->AddImpulse(Move, FName(""), true);
		SlingBandTimeLine.PlayFromStart();
	}
}

void ACPP_SlingBand::SlingBandPlay(float Value)
{
	SlingBand->SetScalarParameterValueOnMaterials(FName("MorphPercent"), Value);
}


