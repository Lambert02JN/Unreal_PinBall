// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CPP_PopBumper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitPopBumper);
UCLASS()
class PINBALL_API ACPP_PopBumper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_PopBumper();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Bump(class ACPP_PinBall* Ball);
	UFUNCTION()
	void PopBumperPlay(float Value);

public:	

	UPROPERTY(BlueprintAssignable)
	FHitPopBumper OnHitPopBumper;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "PopBumper")
	class UStaticMeshComponent* BumperBase;
	UPROPERTY(EditDefaultsOnly, Category = "PopBumper")
	class UStaticMeshComponent* BumperBottom;

	UPROPERTY(EditDefaultsOnly, Category = "PopBumper")
	class UCapsuleComponent* Collision;
	UPROPERTY(EditDefaultsOnly, Category = "PopBumper")
	class UPointLightComponent* Light;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* BumperSound;
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class UParticleSystem* Effect;

	UPROPERTY(EditDefaultsOnly, Category = "PopBumper")
	float Power = 30;

	UPROPERTY(EditDefaultsOnly, Category = "PopBumper")
	class UCurveFloat* PopBumperCurve;

	FTimeline PopBumperTimeLine;
};
