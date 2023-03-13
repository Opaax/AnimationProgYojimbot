// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/YBHealthComponent.h"

// Sets default values for this component's properties
UYBHealthComponent::UYBHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UYBHealthComponent::GiveDamage(const float Damage)
{
	m_health -= Damage;

	//Use Setter to broadcast the callback
	//also make sure to clamp the health
	SetHealth(FMath::Clamp(m_health, 0.f, m_maxHealth));
}


// Called when the game starts
void UYBHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//Clamp then set by setter to broadcast the callback
	SetHealth(FMath::Clamp(m_health, 0.f, m_maxHealth));
}


// Called every frame
void UYBHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

