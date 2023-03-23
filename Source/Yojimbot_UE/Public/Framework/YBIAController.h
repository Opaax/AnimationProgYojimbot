// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "YBIAController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * Base controller for AI
 */
UCLASS()
class YOJIMBOT_UE_API AYBIAController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = AI, meta = (DisplayName = "BlackboardComponent"))
	TObjectPtr<UBlackboardComponent> m_blackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = AI, meta = (DisplayName = "BehaviorTreeComponent"))
	TObjectPtr<UBehaviorTreeComponent> m_behaviorTreeComponent;

	/////////// BLACKBOARD //////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blackboard/Name", meta = (DisplayName = "OnSightKeyName"))
	FName m_isOnSightKeyName = FName("bIsOnSight");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackboard/HashID")
	uint8 m_isOnSightKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blackboard/Name", meta = (DisplayName = "TargetActorKeyName"))
	FName m_targetActorKeyName = FName("TargetActor");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackboard/HashID")
	uint8 m_targetActorKey;
	/////////// END BLACKBOARD //////////

protected:
	UFUNCTION(BlueprintCallable, Category = "Blackboard/HashID")
	virtual void GetHashBlackboardIDs();

public:
	AYBIAController();
	
//////////// OVERRIDE ////////////
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
