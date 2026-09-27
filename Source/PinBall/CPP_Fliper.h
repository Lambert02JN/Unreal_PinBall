// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Enum.h"
#include "CPP_Fliper.generated.h"

UCLASS()
class PINBALL_API ACPP_Fliper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Fliper();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	void SetFlipper();

	void FlipperUp();
	void FlipperDown();

	EDirectionType GetFlipperType() { return FlipperType; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Flipper")
	class UStaticMeshComponent* Flipper;

	UPROPERTY(EditDefaultsOnly, Category = "Flipper")
	EDirectionType FlipperType;

	FRotator StartRotation;
	FRotator EndRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* FlipperLeft;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* FlipperRight;
};
