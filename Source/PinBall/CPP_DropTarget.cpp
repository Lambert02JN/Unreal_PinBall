// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DropTarget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ACPP_DropTarget::ACPP_DropTarget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DropTarget = CreateDefaultSubobject<UStaticMeshComponent>(FName("DropTarget"));

	DropTarget->SetNotifyRigidBodyCollision(true);
	SetRootComponent(DropTarget);

	DropText = CreateDefaultSubobject<UTextRenderComponent>(FName("DropText"));
	DropText->SetRelativeLocation(FVector(-40, 17, 0));
	DropText->SetRelativeRotation(FRotator(0, 90, 0));
	DropText->SetTextRenderColor(FColor::Black);
	DropText->SetXScale(5);
	DropText->SetYScale(5);
	DropText->SetupAttachment(RootComponent);

}

void ACPP_DropTarget::BeginPlay()
{
	Super::BeginPlay();

	DropTarget->OnComponentHit.AddDynamic(this, &ACPP_DropTarget::OnHit);
}

void ACPP_DropTarget::Drop()
{
	StartLocation = DropTarget->GetRelativeLocation();
	FVector NewVector = StartLocation;
	NewVector.Z = -110;

	FLatentActionInfo Latentinfo;
	Latentinfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(DropTarget, NewVector, DropTarget->GetRelativeRotation(), false, false, 0.2f, false, EMoveComponentAction::Type::Move, Latentinfo);

	//SE
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DropSound, DropTarget->GetComponentLocation());
}

void ACPP_DropTarget::ResetDrop()
{
	FLatentActionInfo Latentinfo;
	Latentinfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(DropTarget, StartLocation, DropTarget->GetRelativeRotation(), false, false, 0.2f, false, EMoveComponentAction::Type::Move, Latentinfo);

	DropTarget->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACPP_DropTarget::SetDropText(FString NewText)
{
	DropText->SetText(NewText);
}

void ACPP_DropTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DropTarget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->Drop();
	
	OnTargetDrop.ExecuteIfBound();

}
