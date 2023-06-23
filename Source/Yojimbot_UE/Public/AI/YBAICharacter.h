// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Framework/YBCharacter.h"
#include "Perception/AIPerceptionTypes.h"
#include "YBAIState.h"

#include "YBAICharacter.generated.h"

class UAIPerceptionComponent;
class UBehaviorTree;
class AYBIAController;

/**
 * The default character class for YB AI
 */
UCLASS()
class YOJIMBOT_UE_API AYBAICharacter : public AYBCharacter
{
	GENERATED_BODY()

	/******************************** MEMBERS ********************************/	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintGetter = GetYBController, BlueprintSetter = SetYBController, Category = Controller)
	TObjectPtr<AYBIAController> m_YBController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetAIState, BlueprintSetter = SetAIState, Category = AIState)
	EAIState m_AIState = EAIState::EAIS_Dummy;

	/******************************** AI ********************************/

	UPROPERTY(EditDefaultsOnly,BlueprintGetter = GetBehaviorTree, Category = AI, meta = (DisplayName = "BehaviorTree"))
	TObjectPtr<UBehaviorTree> m_behaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	TObjectPtr<UAIPerceptionComponent> m_AIPerceptionComp;

	/******************************** END AI ********************************/

	/******************************** Animation ********************************/	

	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetYawRotationAngleToTarget, BlueprintSetter = SetYawRotationAngleToTarget, Category = "Animation/Settings", meta = (DisplayName = "YawRotationAngleToTarget"))
	float m_yawRotationAngleToTarget = 0;

	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetPitchRotationAngleToTarget, BlueprintSetter = SetPitchRotationAngleToTarget, Category = "Animation/Settings", meta = (DisplayName = "PitchRotationAngleToTarget"))
	float m_pitchRotationAngleToTarget = 0;

	/******************************** End Animation ********************************/

	/******************************** FUNCTIONS ********************************/
protected:

	UFUNCTION(BlueprintCallable, Category = "AI/Perception")
	virtual void InitPerceptionListener();

	UFUNCTION(BlueprintCallable)
	virtual void SetOnSightBlackboardValue(bool NewValue);
	UFUNCTION(BlueprintCallable)
	virtual void SetTargetActorBlackboardValue(AActor* NewValue);

public:
	AYBAICharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OnPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);

	//////// GETTER / SETTER /////////
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const {return m_behaviorTree;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE AYBIAController* GetYBController() const {return m_YBController;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetYawRotationAngleToTarget() const { return m_yawRotationAngleToTarget; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetYawRotationAngleToTarget(float Value) { m_yawRotationAngleToTarget = Value; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetPitchRotationAngleToTarget() const { return m_pitchRotationAngleToTarget; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPitchRotationAngleToTarget(float Value) { m_pitchRotationAngleToTarget = Value; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetYBController(AYBIAController* YBController) { m_YBController = YBController; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EAIState GetAIState() const { return m_AIState; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetAIState(EAIState NewState = EAIState::EAIS_Dummy) { m_AIState = NewState; }

	/******************************** OVERRIDE ********************************/
protected:
	virtual void BeginPlay() override;
};
