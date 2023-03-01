// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/YBWeaponBase.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AYBWeaponBase::AYBWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));
	SetRootComponent(m_rootComp);

	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	m_mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AYBWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AYBWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

