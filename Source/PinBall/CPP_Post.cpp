// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Post.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ACPP_Post::ACPP_Post()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneComponent"));
	SetRootComponent(SceneComponent);

	LeftPost = CreateDefaultSubobject<UStaticMeshComponent>(FName("LeftPost"));
	LeftPost->SetupAttachment(SceneComponent);

	RightPost = CreateDefaultSubobject<UStaticMeshComponent>(FName("RightPost"));
	PostLine = CreateDefaultSubobject<UStaticMeshComponent>(FName("PostLine"));
}

// Called when the game starts or when spawned
void ACPP_Post::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_Post::SetPost()
{
	RightPost->SetRelativeLocation(PostRightLocation);
	auto LeftRotation = UKismetMathLibrary::FindLookAtRotation(LeftPost->GetRelativeLocation(), PostRightLocation);
	LeftPost->SetRelativeRotation(LeftRotation);

	auto RightRotation = UKismetMathLibrary::FindLookAtRotation(PostRightLocation, LeftPost->GetRelativeLocation());
	RightPost->SetRelativeRotation(RightRotation);
	RightPost->SetStaticMesh(LeftPost->GetStaticMesh());

	PostLine->SetRelativeTransform(LeftPost->GetRelativeTransform());
	float NewX = (LeftPost->GetRelativeLocation() - RightPost->GetRelativeLocation()).Size() / 100;
	PostLine->SetRelativeScale3D(FVector(NewX, LeftPost->GetRelativeScale3D().Y, LeftPost->GetRelativeScale3D().Z));
}

// Called every frame
void ACPP_Post::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

