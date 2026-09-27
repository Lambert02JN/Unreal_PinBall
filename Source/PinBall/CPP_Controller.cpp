// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Controller.h"
#include "CPP_Fliper.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_Plunger.h"
#include "CPP_PinBallModeBase.h"
#include "CPP_PinBall.h"



void ACPP_Controller::BeginPlay()
{
	Super::BeginPlay();
	FindAllFlipers();
	FindPlunger();
}

void ACPP_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftFlip", IE_Pressed, this, &ACPP_Controller::LeftPressedFlip);
	InputComponent->BindAction("LeftFlip", IE_Released, this, &ACPP_Controller::LeftReleasedFlip);
	InputComponent->BindAction("RightFlip", IE_Pressed, this, &ACPP_Controller::RightPressedFlip);
	InputComponent->BindAction("RightFlip", IE_Released, this, &ACPP_Controller::RightReleasedFlip);
	InputComponent->BindAction("Charge", IE_Pressed, this, &ACPP_Controller::ChargePiunger);
	InputComponent->BindAction("Charge", IE_Released, this, &ACPP_Controller::ReleasePiunger);

	InputComponent->BindAction("TiltLeft", IE_Pressed, this, &ACPP_Controller::LeftTilt);
	InputComponent->BindAction("TiltRight", IE_Pressed, this, &ACPP_Controller::RightTilt);
}

void ACPP_Controller::FindAllFlipers()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), FlipperClass, Actors);

	for (int i = 0; i < Actors.Num(); i++)
	{
		auto Flipper = Cast<ACPP_Fliper>(Actors[i]);
		if (Flipper->GetFlipperType() == EDirectionType::LEFT)
		{
			LeftFlippers.Add(Flipper);
		}
		else
		{
			RightFlippers.Add(Flipper);
		}
	}
}

void ACPP_Controller::FindPlunger()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), PlungerClass, Actors);

	Plunger = Cast<ACPP_Plunger>(Actors[0]);
}

void ACPP_Controller::LeftPressedFlip()
{
	for (int i = 0; i < LeftFlippers.Num(); i++)
	{
		LeftFlippers[i]->FlipperUp();
	}
}

void ACPP_Controller::LeftReleasedFlip()
{
	for (int i = 0; i < LeftFlippers.Num(); i++)
	{
		LeftFlippers[i]->FlipperDown();
	}
}

void ACPP_Controller::RightPressedFlip()
{
	for (int i = 0; i < RightFlippers.Num(); i++)
	{
		RightFlippers[i]->FlipperUp();
	}
}

void ACPP_Controller::RightReleasedFlip()
{
	for (int i = 0; i < RightFlippers.Num(); i++)
	{
		RightFlippers[i]->FlipperDown();
	}
}

void ACPP_Controller::ChargePiunger()
{
	Plunger->Charge();
}

void ACPP_Controller::ReleasePiunger()
{
	Plunger->Release();
}

void ACPP_Controller::Tilt(EDirectionType Type)
{
	const auto GameMode = Cast<ACPP_PinBallModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode->TiltCount >= 1)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), PinBallClass, Actors);

		if (Actors.Num() >= 1)
		{
			for (int i = 0; i < Actors.Num(); i++)
			{
				const auto Ball = Cast<ACPP_PinBall>(Actors[i])->GetMesh();

				auto Impulse = Type == EDirectionType::LEFT ? FVector(0, -500, 0) : FVector(0, 500, 0);

				Ball->AddImpulse(Impulse, "None", true);
			}

			//CameraShake
			FRotator Rotator = Type == EDirectionType::LEFT ? PlayerCameraManager->GetCameraRotation() : FRotator(0, 0, 180);
			ClientStartCameraShake(ShakeClass, 1.0f, ECameraShakePlaySpace::UserDefined, Rotator);

			GameMode->TiltCount--;
		}
	}
	
}

void ACPP_Controller::LeftTilt()
{
	Tilt(EDirectionType::LEFT);
}

void ACPP_Controller::RightTilt()
{
	Tilt(EDirectionType::RIGHT);
}
