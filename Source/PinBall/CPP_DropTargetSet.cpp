// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DropTargetSet.h"
#include "Kismet/KismetStringLibrary.h"
#include "CPP_DropTarget.h"
#include "Kismet/KismetSystemLibrary.h"

ACPP_DropTargetSet::ACPP_DropTargetSet()
{
	
}

void ACPP_DropTargetSet::BeginPlay()
{
	Super::BeginPlay();
	TargetCounter = DropTargets.Num();
	for (int i = 0; i < TargetCounter; i++)
	{
		DropTargets[i]->OnTargetDrop.BindUObject(this, &ACPP_DropTargetSet::TargetDropProcess);
	}
}

void ACPP_DropTargetSet::SetPost()
{
	Super::SetPost();
	// set word
	PostString = PostString.ToUpper();
	auto StringArray = UKismetStringLibrary::GetCharacterArrayFromString(PostString);

	TargetCounter = StringArray.Num();
	for (int i = 0; i < TargetCounter; i++)
	{
		FTransform NewTransform;
		float LineSize = (LeftPost->GetComponentLocation() - RightPost->GetComponentLocation()).Size();

		auto TargetToPost = LeftPost->GetForwardVector() * ((i + 1) * (LineSize / (TargetCounter + 1)));
		auto NewLocation = LeftPost->GetComponentLocation()+TargetToPost + (LeftPost->GetRightVector() * 30);

		// Add Actor
		auto NewTarget = GetWorld()->SpawnActor<ACPP_DropTarget>(DropTargetClass, NewLocation, LeftPost->GetComponentRotation());
		DropTargets.Add(NewTarget);
		NewTarget->AttachToActor(SceneComponent->GetAttachmentRootActor(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));

		// Set Word
		NewTarget->SetDropText(StringArray[i]);

	}

}

void ACPP_DropTargetSet::TargetDropProcess()
{
	TargetCounter--;

	if (TargetCounter <= 0)
	{
		FLatentActionInfo LatentActionInfo;
		LatentActionInfo.CallbackTarget = this;
		FTimerHandle _TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &ACPP_DropTargetSet::ReSet, 1.0f, true);
	}
}

void ACPP_DropTargetSet::ReSet()
{
	if (TargetCounter <= 0)
	{
		for (int i = 0; i < DropTargets.Num(); i++)
		{
			DropTargets[i]->ResetDrop();
		}
		TargetCounter = DropTargets.Num();
		OnHitDropTarget.Broadcast();
	}
}
