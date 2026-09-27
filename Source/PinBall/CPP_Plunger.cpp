// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Plunger.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ACPP_Plunger::ACPP_Plunger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Plunger = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piunger"));
	Plunger->SetRelativeScale3D(FVector(5, 5, 5));

	SetRootComponent(Plunger);
}

// Called when the game starts or when spawned
void ACPP_Plunger::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = Plunger->GetRelativeLocation();
	EndLocation = StartLocation + FVector(-150, 0, 0);

	if (PlungerCurve)
	{
		FOnTimelineFloat TimeLineCallBack;
		TimeLineCallBack.BindUFunction(this, FName("PlungerPlay"));
		PlungerTimeLine.AddInterpFloat(PlungerCurve, TimeLineCallBack);
	}
}

// Called every frame
void ACPP_Plunger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlungerTimeLine.TickTimeline(DeltaTime);
}

void ACPP_Plunger::Charge()
{
	PlungerTimeLine.PlayFromStart();
}

void ACPP_Plunger::PlungerPlay(float Value)
{
	Plunger->SetRelativeLocation(FMath::Lerp(StartLocation, EndLocation, Value));
}

FVector ACPP_Plunger::GetSpawnLocation()
{
	return UKismetMathLibrary::TransformLocation(GetActorTransform(), SpawnLocation);
}

void ACPP_Plunger::Release()
{
	PlungerTimeLine.Stop();
	FLatentActionInfo Latentinfo;
	Latentinfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(Plunger, StartLocation, Plunger->GetRelativeRotation(), false, false, 0.03f, false, EMoveComponentAction::Type::Move, Latentinfo);
}

