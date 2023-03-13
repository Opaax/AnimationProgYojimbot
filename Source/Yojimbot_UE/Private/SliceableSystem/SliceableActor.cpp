// Fill out your copyright notice in the Description page of Project Settings.


#include "SliceableSystem/SliceableActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

//Procedural Mesh
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

//Debug
#include "../../Public/Utils/CustomDebugMacro.h"


// Sets default values
ASliceableActor::ASliceableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	m_meshProceduralComp = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComp"));
	SetRootComponent(m_meshProceduralComp);

	m_baseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	m_baseMeshComp->SetupAttachment(GetRootComponent());

	m_baseMeshComp->ToggleVisibility(false);
	m_baseMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_baseMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	m_baseMeshComp->SetStaticMesh(m_meshToCopy);

	//set collision to ignore pawn
	m_meshProceduralComp->SetGenerateOverlapEvents(true);
	m_meshProceduralComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_meshProceduralComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	m_meshProceduralComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	//Active Physic
	m_meshProceduralComp->bUseComplexAsSimpleCollision = false;
	m_meshProceduralComp->SetSimulatePhysics(true);
}

void ASliceableActor::OnSlice_Implementation(const FVector& ImpactPoint, const FVector& Normal)
{
}

void ASliceableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASliceableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void ASliceableActor::TakeHit(const FVector& ImpactPoint, const APawn* Causer)
//{
//	TakeHit(ImpactPoint, FVector(0,0,1.f), Causer);
//}
//
//void ASliceableActor::TakeHit(const FVector& ImpactPoint,const FVector& Normal,const APawn* Causer)
//{
//	FVector lPlaneNormal = FVector::CrossProduct(GetActorLocation() + GetActorForwardVector(), Normal);
//
//	if (lPlaneNormal.Z < 0)
//	{
//		lPlaneNormal.Z *= -1.f;
//	}
//
//	OnSlice(ImpactPoint, lPlaneNormal);
//}

