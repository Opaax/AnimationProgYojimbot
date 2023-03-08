// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/YBComboComponent.h"
#include "GameFramework/Character.h"

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
		FName lPrevSection = FName(FString::Printf(TEXT("%s%d"), *m_sectionNameMontage.ToString(), m_currentAttackIndex - 1));

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(5, 5, FColor::Yellow, FString::Printf(TEXT("Index: %d, SectionName:%s"), m_currentAttackIndex, *lSectionToJump.ToString()));
		}

		if(!m_linkedAnimInstance->Montage_IsPlaying(m_comboMontage))
			m_linkedAnimInstance->Montage_Play(m_comboMontage);
		else
		{
			m_linkedAnimInstance->Montage_JumpToSection(lSectionToJump, m_comboMontage);
			//m_linkedAnimInstance->Montage_SetNextSection(lPrevSection, lSectionToJump, m_comboMontage);
		}

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

void UYBComboComponent::StopComboAnimation()
{
	if (m_linkedAnimInstance && m_comboMontage)
	{
		//m_linkedAnimInstance->Montage_Stop(.25f,m_comboMontage);

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

