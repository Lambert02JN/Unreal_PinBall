// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DeadArea.h"
#include "Components/BoxComponent.h"
#include "CPP_PinBall.h"

// Sets default values
ACPP_DeadArea::ACPP_DeadArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	Collision->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Collision->SetBoxExtent(FVector(32, 32, 32));
}

// Called when the game starts or when spawned
void ACPP_DeadArea::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACPP_DeadArea::OnOverlapBegin);
}

void ACPP_DeadArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Ball = Cast<ACPP_PinBall>(OtherActor))
	{
		Ball->Destroy();
	}
}

// Called every frame
void ACPP_DeadArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

