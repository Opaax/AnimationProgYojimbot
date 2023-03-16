// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SlicerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USlicerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class YOJIMBOT_UE_API ISlicerInterface
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual FVector GetForwardFromRotation() = 0;
	virtual FVector GetUpFromRotation() = 0;
};
