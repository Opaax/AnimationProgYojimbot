// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"

class APawn;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class YOJIMBOT_UE_API IHitInterface
{
	GENERATED_BODY()

public:

	virtual void TakeHit(const FVector& ImpactPoint, const APawn* Causer) = 0;
};
