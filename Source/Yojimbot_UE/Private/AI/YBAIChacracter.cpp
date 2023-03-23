// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/YBAIChacracter.h"
#include "Perception/AIPerceptionComponent.h"

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
	
}

