// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/YBEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

AYBEnemy::AYBEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	InitMeshCollision();
}

void AYBEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AYBEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYBEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AYBEnemy::InitMeshCollision()
{
	if (USkeletalMeshComponent* lMesh = GetMesh())
	{
		lMesh->SetGenerateOverlapEvents(true);
		lMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		lMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
		lMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	}
}
