// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "YBBTTask_RotateHeadToTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class YOJIMBOT_UE_API UYBBTTask_RotateHeadToTargetActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Node", meta = (DisplayName = "RotateYaw"))
	bool bRotateYaw = true;
	UPROPERTY(EditAnywhere, Category = "Node", meta = (DisplayName = "RotateYaw"))
	bool bRotatePitch = true;

	UPROPERTY(EditAnywhere, Category = "Node", meta = (DisplayName = "MinYaw", EditCondition = "bRotateYaw"))
	float m_minYAW;
	UPROPERTY(EditAnywhere, Category = "Node", meta = (DisplayName = "MaxYaw", EditCondition = "bRotateYaw"))
	float m_maxYAW;

	UPROPERTY(EditAnywhere, Category = "Node", meta = (DisplayName = "MinPitch", EditCondition = "bRotatePitch"))
	float m_minPitch;
	UPROPERTY(EditAnywhere, Category = "Node", meta = (DisplayName = "MaxYaw", EditCondition = "bRotatePitch"))
	float m_maxPitch;

public:

	UYBBTTask_RotateHeadToTargetActor(FObjectInitializer const& ObjectInitializer);	

////////// OVERRIDE //////////
private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

};
