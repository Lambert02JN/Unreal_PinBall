// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Post.generated.h"

UCLASS()
class PINBALL_API ACPP_Post : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Post();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Post")
	virtual void SetPost();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Post")
	class USceneComponent* SceneComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Post")
	class UStaticMeshComponent* LeftPost;
	UPROPERTY(EditDefaultsOnly, Category = "Post")
	class UStaticMeshComponent* RightPost;
	UPROPERTY(EditDefaultsOnly, Category = "Post")
	class UStaticMeshComponent* PostLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post", Meta = (MakeEditWidget = true))
	FVector PostRightLocation;

};
