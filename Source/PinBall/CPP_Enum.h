// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDirectionType : uint8
{
	LEFT   UMETA(DisplayName = "LEFT"),
	RIGHT   UMETA(DisplayName = "RIGHT")
};

class CPP_Enum
{
public:
	CPP_Enum();
	~CPP_Enum();
};
