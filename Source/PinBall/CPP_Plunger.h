// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CPP_Plunger.generated.h"

UCLASS()
class PINBALL_API ACPP_Plunger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Plunger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void PlungerPlay(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Charge();
	void Release();

	FVector GetSpawnLocation();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Piunger")
	class UStaticMeshComponent* Plunger;

	UPROPERTY(EditDefaultsOnly, Category = "Piunger")
	class UCurveFloat* PlungerCurve;

	FTimeline PlungerTimeLine;

	FVector StartLocation;
	FVector EndLocation;

public:
	UPROPERTY(EditAnywhere, Category = "Piunger", Meta = (MakeEditWidget = true))
	FVector SpawnLocation;
};
