// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_Enum.h"
#include "CPP_Controller.generated.h"

/**
 * 
 */

class ACPP_Fliper;
class ACPP_Plunger;
class ACPP_PinBall;

UCLASS()
class PINBALL_API ACPP_Controller : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void FindAllFlipers();
	void FindPlunger();

	void LeftPressedFlip();
	void LeftReleasedFlip();
	void RightPressedFlip();
	void RightReleasedFlip();

	void ChargePiunger();
	void ReleasePiunger();

	void Tilt(EDirectionType Type);
	void LeftTilt();
	void RightTilt();

protected:
	UPROPERTY(EditDefaultsOnly,Category = "Flipper")
	TSubclassOf<ACPP_Fliper> FlipperClass;

	TArray<ACPP_Fliper*> LeftFlippers;
	TArray<ACPP_Fliper*> RightFlippers;

	UPROPERTY(EditDefaultsOnly, Category = "Plunger")
	TSubclassOf<ACPP_Plunger> PlungerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ball")
	TSubclassOf<ACPP_PinBall> PinBallClass;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<class UCameraShakeBase> ShakeClass;

	ACPP_Plunger* Plunger;
};
