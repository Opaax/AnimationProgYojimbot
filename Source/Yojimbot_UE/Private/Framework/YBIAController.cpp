// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/YBIAController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "../../Public/AI/YBAIChacracter.h"
#include "BehaviorTree/BehaviorTree.h"

AYBIAController::AYBIAController()
{
	m_behaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	m_blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AYBIAController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AYBAIChacracter* lCharacter = Cast<AYBAIChacracter>(InPawn))
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