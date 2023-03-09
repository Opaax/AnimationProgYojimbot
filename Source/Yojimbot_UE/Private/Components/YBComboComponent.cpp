// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/YBComboComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"

// Sets default values for this component's properties
UYBComboComponent::UYBComboComponent(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UYBComboComponent::BeginPlay()
{
	Super::BeginPlay();	

	if (ACharacter* lPawnOwner = Cast<ACharacter>(GetOwner()))
	{
		m_linkedAnimInstance = lPawnOwner->GetMesh()->GetAnimInstance();

		if (m_linkedAnimInstance == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("%s linked anim instance is nullptr"), *GetName());
		}
	}

	m_currentAttackIndex = m_startIndexAttack;
}

// Called every frame
void UYBComboComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UYBComboComponent::PlayComboAnimation()
{
	if (m_linkedAnimInstance && m_comboMontage)
	{
		FName lSectionToJump = FName(FString::Printf(TEXT("%s%d"), *m_sectionNameMontage.ToString(), m_currentAttackIndex));

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Index: %d, SectionName:%s"), m_currentAttackIndex, *lSectionToJump.ToString()));
		}

		if (!m_linkedAnimInstance->Montage_IsPlaying(m_comboMontage))
		{
			m_linkedAnimInstance->Montage_Play(m_comboMontage);

			if(!m_linkedAnimInstance->OnPlayMontageNotifyBegin.IsBound())
				m_linkedAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UYBComboComponent::ComboNotifyBegin);

			if(!m_linkedAnimInstance->OnPlayMontageNotifyEnd.IsBound())
				m_linkedAnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &UYBComboComponent::ComboNotifyEnd);
		}
		else
		{
			m_linkedAnimInstance->Montage_JumpToSection(lSectionToJump, m_comboMontage);
		}

		m_comboState = EComboState::ECS_OnAttack;
		m_currentAttackIndex++;
	}
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
		OnComboFinish.Broadcast();

		m_currentAttackIndex = m_startIndexAttack;

		m_comboState = EComboState::ECS_OnWaiting;

		if (!m_linkedAnimInstance->OnPlayMontageNotifyBegin.IsBound())
			m_linkedAnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UYBComboComponent::ComboNotifyBegin);

		if (!m_linkedAnimInstance->OnPlayMontageNotifyEnd.IsBound())
			m_linkedAnimInstance->OnPlayMontageNotifyEnd.RemoveDynamic(this, &UYBComboComponent::ComboNotifyEnd);

		return;
	}

	m_comboState = EComboState::ECS_OnAttackWindow;
}

void UYBComboComponent::ComboNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayLoad)
{
	if (NotifyName.ToString().Equals(FString::Printf(TEXT("%s_Window"), *m_linkedAnimInstance->Montage_GetCurrentSection().ToString())))
	{
		if (!m_linkedAnimInstance->OnPlayMontageNotifyBegin.IsBound())
			m_linkedAnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UYBComboComponent::ComboNotifyBegin);

		if (!m_linkedAnimInstance->OnPlayMontageNotifyEnd.IsBound())
			m_linkedAnimInstance->OnPlayMontageNotifyEnd.RemoveDynamic(this, &UYBComboComponent::ComboNotifyEnd);

		m_currentAttackIndex = m_startIndexAttack;

		m_comboState = EComboState::ECS_OnWaiting;

		OnComboEnd.Broadcast();
	}	
}

void UYBComboComponent::StopComboAnimation()
{
	if (m_linkedAnimInstance && m_comboMontage)
	{
		m_currentAttackIndex = m_startIndexAttack;
	}
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

