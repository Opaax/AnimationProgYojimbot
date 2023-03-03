// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/YBWeaponBase.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Engine.h"

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

	if (m_attackCollision->OnComponentBeginOverlap.IsBound())
	{
		m_attackCollision->OnComponentBeginOverlap.RemoveDynamic(this, &AYBWeaponBase::OnBoxColliderOverlap);
	}
}

void AYBWeaponBase::OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1,4,FColor::Blue,FString("Message"));
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
	m_attackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AYBWeaponBase::DesactivateAttackCollision()
{
	UE_LOG(LogTemp, Warning, TEXT("Desactivate"));

	m_attackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

