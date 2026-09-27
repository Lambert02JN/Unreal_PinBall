// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PinBallModeBase.h"
#include "CPP_Plunger.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_PinBall.h"


void ACPP_PinBallModeBase::BeginPlay()
{
	Super::BeginPlay();
	// Set UI
	UI = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);
	UI->AddToViewport();

	SpawnBall();
}

void ACPP_PinBallModeBase::SpawnBall()
{
	TiltCount = MaxTiltCount;
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), PlungerClass, Actors);

	auto Plunger = Cast<ACPP_Plunger>(Actors[0]);
	//SpawnBall
	auto Ball = GetWorld()->SpawnActor(BallClass);

	Ball->SetActorLocation(Plunger->GetSpawnLocation());

	// Bind Destroy Ball
	Ball->OnDestroyed.AddDynamic(this, &ACPP_PinBallModeBase::OnBallDestroyed);
	BallDestroyed.Broadcast();
}

void ACPP_PinBallModeBase::OnBallDestroyed(AActor* Actor)
{
	UE_LOG(LogTemp, Log, TEXT("SpawnBall"));
	SpawnBall();
}


