// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/YBAICharacter.h"
#include "../../Public/Framework/YBIAController.h"
#include "Perception/AIPerceptionComponent.h"
#include "../../Public/Utils/CustomDebugMacro.h"

AYBAICharacter::AYBAICharacter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	m_AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

void AYBAICharacter::BeginPlay()
{
	Super::BeginPlay();

	InitPerceptionListener();
}

void AYBAICharacter::InitPerceptionListener()
{
	m_AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AYBAICharacter::OnPerceptionUpdate);
}

void AYBAICharacter::OnPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
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

void AYBAICharacter::SetOnSightBlackboardValue(bool NewValue)
{
	if (m_YBController)
	{
		m_YBController->SetOnSightValue(NewValue);
	}
}

void AYBAICharacter::SetTargetActorBlackboardValue(AActor* NewValue)
{
	if (m_YBController)
	{
		m_YBController->SetTargetActorValue(NewValue);
	}
}

