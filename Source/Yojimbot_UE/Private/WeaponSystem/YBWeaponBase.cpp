// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/YBWeaponBase.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../Public/DamageSystem/HitInterface.h"

// Sets default values
AYBWeaponBase::AYBWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));
	SetRootComponent(m_rootComp);

	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	m_mesh->SetupAttachment(GetRootComponent());

	m_attackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	m_attackCollision->SetupAttachment(GetRootComponent());
	m_attackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_attackCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	m_attackCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	m_startTrace = CreateDefaultSubobject<USceneComponent>(TEXT("StartTrace"));
	m_startTrace->SetupAttachment(m_attackCollision);

	m_endTrace = CreateDefaultSubobject<USceneComponent>(TEXT("EndTrace"));
	m_endTrace->SetupAttachment(m_attackCollision);
}

// Called when the game starts or when spawned
void AYBWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	m_attackCollision->OnComponentBeginOverlap.AddDynamic(this, &AYBWeaponBase::OnBoxColliderOverlap);
}

void AYBWeaponBase::BeginDestroy()
{
	Super::BeginDestroy();

	if (m_attackCollision && m_attackCollision->OnComponentBeginOverlap.IsBound())
	{
		m_attackCollision->OnComponentBeginOverlap.RemoveDynamic(this, &AYBWeaponBase::OnBoxColliderOverlap);
	}
}

void AYBWeaponBase::OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon Overlap"));

	if (GEngine)
	{
		FString lMSG = FString::Printf(TEXT("Weapon: %s, Overlap this Actor: %s"), *GetName(), *OtherActor->GetName());
		GEngine->AddOnScreenDebugMessage(1,4,FColor::Blue, lMSG);
	}

	FHitResult lTraceResult;

	m_actorToIgnoreWhileOverlaping.AddUnique(this);

	UKismetSystemLibrary::BoxTraceSingle(this, m_startTrace->GetComponentLocation(), m_endTrace->GetComponentLocation(),
		m_boxTraceHalfSize, m_startTrace->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1, false, m_actorToIgnoreWhileOverlaping , 
		EDrawDebugTrace::None, lTraceResult, true, FColor::Red, FColor::Green, 5.f);

	if (AActor* lHitActor = lTraceResult.GetActor())
	{
		if (IHitInterface* lHitInt = Cast<IHitInterface>(lHitActor))
		{
			m_actorToIgnoreWhileOverlaping.AddUnique(lHitActor);

			lHitInt->TakeHit(lTraceResult.ImpactPoint, Cast<APawn>(GetOwner()));
		}
	}
}

// Called every frame
void AYBWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYBWeaponBase::ActivateAttackCollision()
{
	UE_LOG(LogTemp, Warning, TEXT("Activate"));
	m_attackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AYBWeaponBase::DesactivateAttackCollision()
{
	UE_LOG(LogTemp, Warning, TEXT("Desactivate"));

	m_attackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_actorToIgnoreWhileOverlaping.Empty();
}

