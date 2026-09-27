// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "CPP_PinBallModeBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBallDestroyed);
UCLASS()
class ACPP_PinBallModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	virtual void BeginPlay() override;

	void SpawnBall();

private:
	UFUNCTION()
	void OnBallDestroyed(AActor* Actor);

public:

	int32 TiltCount;

	UPROPERTY(EditDefaultsOnly, Category = "PinBallModeBase")
	int32 MaxTiltCount = 4;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> WidgetClass;
	UPROPERTY()
	UUserWidget* UI;
	UPROPERTY(EditDefaultsOnly, Category = "Plunger")
	TSubclassOf<class ACPP_Plunger> PlungerClass;
	UPROPERTY(EditDefaultsOnly, Category = "Ball")
	TSubclassOf<class ACPP_PinBall> BallClass;

	UPROPERTY(BlueprintAssignable)
	FBallDestroyed BallDestroyed;
};
