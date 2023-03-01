// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControlRig.h"
#include "YBPlayerCharacterControlRig.generated.h"

/**
 * 
 */
UCLASS()
class YOJIMBOT_UE_API UYBPlayerCharacterControlRig : public UControlRig
{
	GENERATED_BODY()
protected:

	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	float m_zTraceUpOffsetDistance = 50;
	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	float m_zTraceDistance = 150;
	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	float m_zAdditionalOffset = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	bool bLeftFootFloorFound = true;
	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	bool bRightFootFloorFound = true;

	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float m_zOffset_LTarget = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float m_zOffset_RTarget = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float m_zOffsetL = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float m_zOffsetR = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float m_zOffsetPelvis = 0;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
	bool bShouldTrace = true;
};
