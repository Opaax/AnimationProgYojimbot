// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YBComboComponent.generated.h"

class UAnimMontage;
class UAnimInstance;

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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter = GetNumAttackInCombo, Category = ComboComponent, meta = (DisplayName = "NumAttackInCombo"))
	int32 m_numAttackInCombo;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter = GetStartIndexAttack, Category = ComboComponent, meta = (DisplayName = "StartIndexAttack"))
	int32 m_startIndexAttack;

	UPROPERTY(BlueprintReadwrite, VisibleAnywhere, BlueprintGetter = GetCurrentAttackIndex, Category = ComboComponent)
	int32 m_currentAttackIndex;

public:

protected:

public:	
	UYBComboComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void PlayComboAnimation();

	UFUNCTION(BlueprintCallable)
	void StopComboAnimation();

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

/////////// OVERRRIDES /////////
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
