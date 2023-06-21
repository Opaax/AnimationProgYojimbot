// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/YBIAController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "../../Public/AI/YBAICharacter.h"
#include "BehaviorTree/BehaviorTree.h"

AYBIAController::AYBIAController()
{
	m_behaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	m_blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AYBIAController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AYBAICharacter* lCharacter = Cast<AYBAICharacter>(InPawn))
	{
		lCharacter->SetYBController(this);

		if (IsValid(m_blackboardComp) && IsValid(m_behaviorTreeComponent))
		{
			m_blackboardComp->InitializeBlackboard(*lCharacter->GetBehaviorTree()->BlackboardAsset);

			m_behaviorTreeComponent->StartTree(*lCharacter->GetBehaviorTree());

			GetHashBlackboardIDs();
		}
	}
}

void AYBIAController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AYBIAController::GetHashBlackboardIDs()
{
	if (m_blackboardComp && m_blackboardComp->GetBlackboardAsset())
	{
		m_isOnSightKey = m_blackboardComp->GetKeyID(m_isOnSightKeyName);
		m_targetActorKey = m_blackboardComp->GetKeyID(m_targetActorKeyName);
	}
}

void AYBIAController::SetOnSightValue(bool NewValue)
{
	if (m_blackboardComp)
	{
		m_blackboardComp->SetValueAsBool(m_blackboardComp->GetKeyName(m_isOnSightKey), NewValue);
	}
}

void AYBIAController::SetTargetActorValue(AActor* NewValue)
{
	if (m_blackboardComp) 
	{
		m_blackboardComp->SetValueAsObject(m_blackboardComp->GetKeyName(m_targetActorKey), NewValue);
	}
}