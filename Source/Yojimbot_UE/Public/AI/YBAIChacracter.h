// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Framework/YBCharacter.h"
#include "Perception/AIPerceptionTypes.h"

#include "YBAIChacracter.generated.h"

class UAIPerceptionComponent;
class UBehaviorTree;
class AYBIAController;

/**
 * 
 */
UCLASS()
class YOJIMBOT_UE_API AYBAIChacracter : public AYBCharacter
{
	GENERATED_BODY()
	
protected:

	///////////// AI ///////////////
	UPROPERTY(EditDefaultsOnly,BlueprintGetter = GetBehaviorTree, Category = AI, meta = (DisplayName = "BehaviorTree"))
	TObjectPtr<UBehaviorTree> m_behaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	TObjectPtr<UAIPerceptionComponent> m_AIPerceptionComp;
	/////////// END AI //////////////

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, BlueprintGetter = GetYBController, BlueprintSetter = SetYBController, Category = Controller)
	TObjectPtr<AYBIAController> m_YBController;

protected:

	UFUNCTION(BlueprintCallable, Category = "AI/Perception")
	virtual void InitPerceptionListener();

public:
	AYBAIChacracter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OnPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const {return m_behaviorTree;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE AYBIAController* GetYBController() const {return m_YBController;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE void SetYBController(AYBIAController* YBController) { m_YBController = YBController; }

//////////// OVERRRIDE ///////////////
protected:
	virtual void BeginPlay() override;
};
