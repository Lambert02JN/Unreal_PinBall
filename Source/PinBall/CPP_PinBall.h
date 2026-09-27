// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_PinBall.generated.h"


UCLASS()
class PINBALL_API ACPP_PinBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_PinBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Move(float DeltaTime);
	void SetAudio();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UStaticMeshComponent* GetMesh() { return PinBall; }


protected:
	UPROPERTY(EditDefaultsOnly, Category = "PinBall")
	class UStaticMeshComponent* PinBall;
public:
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float Speed = 2000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float Stickness = 5000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	class UAudioComponent* Audio;
};
