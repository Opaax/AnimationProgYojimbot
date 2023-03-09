// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../ComboSystem/YBComboState.h"
#include "YBComboComponent.generated.h"

class UAnimMontage;
class UAnimInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FComboDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YOJIMBOT_UE_API UYBComboComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, BlueprintGetter = GetComboMontage, Category = ComboComponent, meta = (DisplayName = "ComboMontage"))
	UAnimMontage* m_comboMontage = nullptr;

	UPROPERTY(BlueprintReadOnly, visibleAnywhere, Category = ComboComponent, meta = (DisplayName = "AnimInstance"))
	TObjectPtr<UAnimInstance> m_linkedAnimInstance;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter = GetSectionNameBase, Category = ComboComponent, meta = (DisplayName = "SectionNameBase"))
	FName m_sectionNameMontage = FName("Attack_");

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = ComboComponent, meta = (DisplayName = "NotifyWindowSuffix"))
	FString m_notifyWindowSuffix = FString("_Window");

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = ComboComponent, meta = (DisplayName = "EndComboNotifyName"))
	FName m_endComboNotifyName = FName("End_Combo");

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter = GetNumAttackInCombo, Category = ComboComponent, meta = (DisplayName = "NumAttackInCombo"))
	int32 m_numAttackInCombo;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter = GetStartIndexAttack, Category = ComboComponent, meta = (DisplayName = "StartIndexAttack"))
	int32 m_startIndexAttack;

	UPROPERTY(BlueprintReadwrite, VisibleAnywhere, BlueprintGetter = GetCurrentAttackIndex, Category = ComboComponent)
	int32 m_currentAttackIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetComboState, Category = ComboComponent, meta = (DisplayName = "ComboState"))
	EComboState m_comboState = EComboState::ECS_OnWaiting;

public:

	UPROPERTY(BlueprintAssignable, Category = Callback)
	FComboDelegate OnComboEnd;

	UPROPERTY(BlueprintAssignable, Category = Callback)
	FComboDelegate OnComboFinish;

	UPROPERTY(BlueprintAssignable, Category = Callback)
	FComboDelegate OnComboCancel;

protected:

public:	
	UYBComboComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void PlayComboAnimation();

	UFUNCTION(BlueprintCallable)
	void StopComboAnimation();

	UFUNCTION()
	void ComboNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayLoad);
	UFUNCTION()
	void ComboNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayLoad);

	/////////// GETTER / SETTER ///////////
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UAnimMontage* GetComboMontage() const { return m_comboMontage; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE FName GetSectionNameBase() const { return m_sectionNameMontage; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetNumAttackInCombo() const { return m_numAttackInCombo; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetCurrentAttackIndex() const { return m_numAttackInCombo; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetStartIndexAttack() const { return m_startIndexAttack; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EComboState GetComboState() const { return m_comboState; }

/////////// OVERRRIDES /////////
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
