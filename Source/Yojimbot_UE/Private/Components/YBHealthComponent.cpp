// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/YBHealthComponent.h"

// Sets default values for this component's properties
UYBHealthComponent::UYBHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UYBHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UYBHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

