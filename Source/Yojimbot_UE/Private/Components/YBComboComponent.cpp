// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/YBComboComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"

#include "../../Public/Utils/CustomDebugMacro.h"

UYBComboComponent::UYBComboComponent(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UYBComboComponent::BeginPlay()
{
	Super::BeginPlay();	

	if (ACharacter* lPawnOwner = Cast<ACharacter>(GetOwner()))
	{
		//Get the PTR of the current anim instance link to the owner
		m_linkedAnimInstance = lPawnOwner->GetMesh()->GetAnimInstance();

		//Error message
		if (m_linkedAnimInstance == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("%s linked anim instance is nullptr"), *GetName());
		}
	}

	//make sure that the index is set with the Start index
	ResetIndexInternal();
}

void UYBComboComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UYBComboComponent::ListenMontageEvent()
{
	if (!m_linkedAnimInstance->OnPlayMontageNotifyBegin.IsBound())
		m_linkedAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UYBComboComponent::ComboNotifyBegin);

	if (!m_linkedAnimInstance->OnPlayMontageNotifyEnd.IsBound())
		m_linkedAnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &UYBComboComponent::ComboNotifyEnd);
}

void UYBComboComponent::ResetIndexInternal()
{
	m_currentAttackIndex = m_startIndexAttack;
}

void UYBComboComponent::StopListeningMontageEvent()
{
	if (!m_linkedAnimInstance->OnPlayMontageNotifyBegin.IsBound())
		m_linkedAnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UYBComboComponent::ComboNotifyBegin);

	if (!m_linkedAnimInstance->OnPlayMontageNotifyEnd.IsBound())
		m_linkedAnimInstance->OnPlayMontageNotifyEnd.RemoveDynamic(this, &UYBComboComponent::ComboNotifyEnd);
}

void UYBComboComponent::PlayComboAnimation()
{
	if (m_linkedAnimInstance && m_comboMontage)
	{
		FName lSectionToJump = FName(FString::Printf(TEXT("%s%d"), *m_sectionNameMontage.ToString(), m_currentAttackIndex));

		if (!m_linkedAnimInstance->Montage_IsPlaying(m_comboMontage))
		{
			m_linkedAnimInstance->Montage_Play(m_comboMontage);

			ListenMontageEvent();
		}
		else
		{
			m_linkedAnimInstance->Montage_JumpToSection(lSectionToJump, m_comboMontage);
		}

		m_comboState = EComboState::ECS_OnAttack;
		m_currentAttackIndex++;
	}
	//Error messages
	else
	{
		if (!m_linkedAnimInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("%s linked anim instance is nullptr"), *GetName());
		}

		if (!m_comboMontage)
		{
			UE_LOG(LogTemp, Error, TEXT("%s m_comboMontage is nullptr"), *GetName());
		}
	}
}

void UYBComboComponent::ComboNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayLoad)
{
	if (NotifyName == m_endComboNotifyName)
	{
		m_comboState = EComboState::ECS_OnWaiting;

		ResetIndexInternal();
		StopListeningMontageEvent();
		
		OnComboFinish.Broadcast(); //Callback that the combo is finish

		return;
	}

	m_comboState = EComboState::ECS_OnAttackWindow;
}

void UYBComboComponent::ComboNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayLoad)
{
	//Create name to compare with notify name
	FName lNameToCheck = FName(FString::Printf(TEXT("%s%s"), *m_linkedAnimInstance->Montage_GetCurrentSection().ToString(), *m_notifyWindowSuffix));

	UE_LOG(LogTemp, Error, TEXT("%s"), *lNameToCheck.ToString());

	if (NotifyName == lNameToCheck)
	{
		m_comboState = EComboState::ECS_OnWaiting;

		ResetIndexInternal();
		StopListeningMontageEvent();

		OnComboEnd.Broadcast();
	}	

	m_comboState = EComboState::ECS_OnWaiting;

	ResetIndexInternal();
	StopListeningMontageEvent();

	OnComboEnd.Broadcast();
}

void UYBComboComponent::StopComboAnimation()
{
	if (m_linkedAnimInstance && m_comboMontage)
	{
		m_linkedAnimInstance->Montage_Stop(m_stopBlendoutTime, m_comboMontage);

		ResetIndexInternal();
		StopListeningMontageEvent();
	}
	//Error Message
	else
	{
		if (!m_linkedAnimInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("%s linked anim instance is nullptr"), *GetName());
		}

		if (!m_comboMontage)
		{
			UE_LOG(LogTemp, Error, TEXT("%s m_comboMontage is nullptr"), *GetName());
		}
	}
}

void UYBComboComponent::CancelComboAnimation()
{
	UE_LOG(LogTemp, Error, TEXT("Not implemented Yet"));
}

void UYBComboComponent::ResetCombo()
{
	ResetIndexInternal();
	StopComboAnimation();
}
