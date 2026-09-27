// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Post.h"
#include "CPP_DropTargetSet.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitDropTarget);
class ACPP_DropTarget;

UCLASS()
class PINBALL_API ACPP_DropTargetSet : public ACPP_Post
{
public:
	GENERATED_BODY()

	ACPP_DropTargetSet();
protected:
	virtual void BeginPlay() override;

	virtual void SetPost() override;

public:
	UPROPERTY(EditAnywhere, Category = "Post")
	FString PostString;

	int32 TargetCounter;

	UPROPERTY(EditDefaultsOnly, Category = "Post")
	TSubclassOf<ACPP_DropTarget> DropTargetClass;
	UPROPERTY(EditAnywhere, Category = "Post")
	TArray<ACPP_DropTarget*> DropTargets;

	UPROPERTY(BlueprintAssignable)
	FHitDropTarget OnHitDropTarget;

private:
	UFUNCTION()
	void TargetDropProcess();

	void ReSet();
};
