// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_DropTarget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOnTargetDrop);

UCLASS()
class ACPP_DropTarget : public AActor
{
public:
	GENERATED_BODY()

	// Sets default values for this actor's properties
	ACPP_DropTarget();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Target")
	class UStaticMeshComponent* DropTarget;

	UPROPERTY(EditDefaultsOnly, Category = "Target")
	class UTextRenderComponent* DropText;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* DropSound;

	FVector StartLocation;

public:
	UFUNCTION()
	void Drop();
	
	UFUNCTION()
	void ResetDrop();

	UFUNCTION()
	void SetDropText(FString NewText);

	FOnTargetDrop OnTargetDrop;

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
