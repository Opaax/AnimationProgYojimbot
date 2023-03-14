// Fill out your copyright notice in the Description page of Project Settings.


#include "SliceableSystem/SliceableActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "../../Public/SliceableSystem/SlicerInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

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

void ASliceableActor::BeginPlay()
{
	Super::BeginPlay();

	m_meshProceduralComp->OnComponentBeginOverlap.AddDynamic(this, &ASliceableActor::OnProceduralComponentOverlap);
}

void ASliceableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASliceableActor::OnProceduralComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsCanSlice())
	{
		if (UProceduralMeshComponent* lProcMeshComp = Cast<UProceduralMeshComponent>(OverlappedComponent))
		{
			m_sliceState = ESliceActorState::ESAS_OnSlice;
			ProductSlice(OtherActor, lProcMeshComp);
		}
	}
}

void ASliceableActor::ProductSlice(AActor* Causer, UProceduralMeshComponent* OverlappedComp)
{
	FVector lSlicePlanePosition;
	FVector lHitNormal;
	FVector lHitUp;
	FVector lPlaneNormal;
	FVector lRightVectorOfHitNormal;

	TArray<AActor*> lIgnoreList;
	FHitResult lTraceResult;

	//check the causer is a slicer
	if (ISlicerInterface* lSlicer = Cast<ISlicerInterface>(Causer))
	{
		lSlicePlanePosition = Causer->GetActorLocation();
		lHitNormal = lSlicer->GetForwardFromRotation().GetSafeNormal() * -1;
		lHitUp = lSlicer->GetUpFromRotation().GetSafeNormal();

		//ignore for this call the slicer
		lIgnoreList.AddUnique(Causer);

		//Trace to touched comp to get more precise impact point
		UKismetSystemLibrary::LineTraceSingle
		(this, lSlicePlanePosition, OverlappedComp->GetComponentLocation(),
			ETraceTypeQuery::TraceTypeQuery1, false, lIgnoreList, EDrawDebugTrace::None, lTraceResult, false, FColor::Yellow, FColor::Green, 20.f);
	}

	//Replace slice pos into impact point
	lSlicePlanePosition = lTraceResult.ImpactPoint;

	//Rotate the hit normal by -90 degree to find out the right vector by the UP world axis
	lRightVectorOfHitNormal = UKismetMathLibrary::RotateAngleAxis(lHitNormal, -90, FVector(0, 0, 1));

	//Get the Up vector to project the normal plane on it
	lPlaneNormal = FVector::CrossProduct(lRightVectorOfHitNormal, lHitNormal).GetSafeNormal();

	//Call to call BP event
	OnSlice(lSlicePlanePosition, lPlaneNormal, OverlappedComp);

	GetWorld()->GetTimerManager().SetTimer(SliceFrequencyTimerHandler,this,&ASliceableActor::OnSliceEnableForNextSlice, m_sliceFrequency, false);

	//Draw Debug
	/*DRAW_SPHERE_AT(lSlicePlanePosition, .5f);
	DRAW_ARROW(lSlicePlanePosition, lSlicePlanePosition + (lHitNormal.GetSafeNormal() * 100.f), FColor::Blue);
	DRAW_ARROW(lSlicePlanePosition, lSlicePlanePosition + (lRightVectorOfHitNormal * 100.f), FColor::Green);
	DRAW_ARROW(lSlicePlanePosition, lSlicePlanePosition + (lPlaneNormal * 100.f), FColor::Red);*/
}

void ASliceableActor::OnSliceEnableForNextSlice()
{
	if (++m_sliceCount >= m_maxSlice)
	{
		m_sliceState = ESliceActorState::ESAS_OnDisappear;

		GetWorld()->GetTimerManager().ClearTimer(SliceFrequencyTimerHandler);

		SetLifeSpan(3.f);

		return;
		//TODO make dissapear slice with effect....
	}

	m_sliceState = ESliceActorState::ESAS_OnWaiting;
}

void ASliceableActor::RefreshEventHandlerFromProcMeshComp()
{
	for (int i = m_slicedComp.Num() - 1; i >= 0; i--)
	{
		if (m_slicedComp[i]->OnComponentBeginOverlap.IsBound())
		{
			m_slicedComp[i]->OnComponentBeginOverlap.RemoveDynamic(this, &ASliceableActor::OnProceduralComponentOverlap);
		}
	}

	for (int i = m_slicedComp.Num() - 1; i >= 0; i--)
	{
		if (!m_slicedComp[i]->OnComponentBeginOverlap.IsBound())
		{
			m_slicedComp[i]->OnComponentBeginOverlap.AddDynamic(this, &ASliceableActor::OnProceduralComponentOverlap);
		}
	}
}

void ASliceableActor::BindNewToCompToBeginOverlap(UProceduralMeshComponent* NewComp)
{
	if (NewComp)
	{
		m_slicedComp.Add(NewComp);

		NewComp->OnComponentBeginOverlap.AddDynamic(this, &ASliceableActor::OnProceduralComponentOverlap);
	}

	RefreshEventHandlerFromProcMeshComp();
}

bool ASliceableActor::IsCanSlice()
{
	return m_sliceState != ESliceActorState::ESAS_OnSlice && m_sliceState != ESliceActorState::ESAS_OnDisappear;
}

void ASliceableActor::OnSlice_Implementation(const FVector& ImpactPoint, const FVector& Normal, UProceduralMeshComponent* CompOverlapped)
{

}

