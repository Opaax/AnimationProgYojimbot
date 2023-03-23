// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/YBAIChacracter.h"
#include "../../Public/Framework/YBIAController.h"
#include "Perception/AIPerceptionComponent.h"
#include "../../Public/Utils/CustomDebugMacro.h"

AYBAIChacracter::AYBAIChacracter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	m_AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

void AYBAIChacracter::BeginPlay()
{
	Super::BeginPlay();

	InitPerceptionListener();
}

void AYBAIChacracter::InitPerceptionListener()
{
	m_AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AYBAIChacracter::OnPerceptionUpdate);
}

void AYBAIChacracter::OnPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	//DEBUG_LOG(TEXT("%s, Stimulus Tag"), *Stimulus.Type.Name.ToString());
	/*
	* TODO
	* Change Check string
	* check Id ?
	*/
	if (Stimulus.Type.Name.ToString().Contains("Sight"))
	{
		if (!Stimulus.IsExpired())
		{
			SetOnSightBlackboardValue(true);
			SetTargetActorBlackboardValue(Actor);
		}
		else
		{
			SetOnSightBlackboardValue(false);
			SetTargetActorBlackboardValue(nullptr);
		}
	}
}

void AYBAIChacracter::SetOnSightBlackboardValue(bool NewValue)
{
	if (m_YBController)
	{
		m_YBController->SetOnSightValue(NewValue);
	}
}

void AYBAIChacracter::SetTargetActorBlackboardValue(AActor* NewValue)
{
	if (m_YBController)
	{
		m_YBController->SetTargetActorValue(NewValue);
	}
}

