// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/YBEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Public/Components/YBHealthComponent.h"
#include "../../Public/UI/YBEnemyLifeBar.h"
#include "../../Public/Utils/CustomDebugMacro.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Controller.h"
#include "Components/WidgetComponent.h"

AYBEnemy::AYBEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	InitMeshCollision();
	InitHealthComponent();

	m_lifeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LifeWidgetComp"));
	m_lifeWidgetComponent->SetupAttachment(GetRootComponent());
	m_lifeWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	m_lifeWidgetComponent->SetWidgetClass(m_healthWidgetCompClass);
}

void AYBEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (m_lifeWidgetComponent != nullptr)
	{
		m_healthWidget = Cast<UYBEnemyLifeBar>(m_lifeWidgetComponent->GetWidget());

		if (m_healthWidget && m_healthComponent)
		{
			m_healthWidget->InitializeValues(m_healthComponent->GetMaxHealth(), m_healthComponent->GetHealth());
		}
	}

	if(m_healthComponent != nullptr)
		m_healthComponent->OnHealthUpdate.AddDynamic(this, &AYBEnemy::OnHealthCompUpdate);
}

void AYBEnemy::OnHealthCompUpdate(const float Currenthealth, const float HealthRatio)
{
	m_healthWidget->UpdateLife(Currenthealth, HealthRatio);
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
		lMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		lMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		lMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
		lMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		lMesh->SetGenerateOverlapEvents(true);
	}
}

void AYBEnemy::InitHealthComponent()
{
	m_healthComponent = CreateDefaultSubobject<UYBHealthComponent>(TEXT("HealthComponent"));
}

void AYBEnemy::ComputeHitReactionAngle(const FVector& ImpactPoint, const APawn* Causer)
{
	const FVector lForward = GetActorForwardVector();
	//place the impact loc Z to actor Z
	const FVector lImpactReplaced = FVector(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector lToHit = (lImpactReplaced - GetActorLocation()).GetSafeNormal();

	//Get cos angle from vector
	float lAngle = FVector::DotProduct(lForward, lToHit);
	//inverse cos to rad angle
	lAngle = FMath::Acos(lAngle);
	//rad to degree
	lAngle = FMath::RadiansToDegrees(lAngle);

	const FVector lCross = FVector::CrossProduct(lForward, lToHit);

	if (lCross.Z < 0)
	{
		lAngle *= -1.f;
	}

	FName lMontageLayerName = m_hitBackwardLayerName;

	if (lAngle >= -45 && lAngle < 45.f)
	{
		lMontageLayerName = m_hitForwardLayerName;
	}
	else if (lAngle < -45.f && lAngle > -135.f)
	{
		lMontageLayerName = m_hitRightLayerName;
	}
	else if (lAngle >= 45.f && lAngle <= 135.f)
	{
		lMontageLayerName = m_hitLeftLayerName;
	}

	GetMesh()->GetAnimInstance()->Montage_Play(m_hitReactionMontage);
	GetMesh()->GetAnimInstance()->Montage_JumpToSection(lMontageLayerName, m_hitReactionMontage);

	DRAW_ARROW(GetActorLocation(), GetActorLocation() + (lForward * 400.f), FColor::Blue);
	DRAW_ARROW(GetActorLocation(), GetActorLocation() + (lToHit * 400.f), FColor::Green);

	if (GEngine)
	{
		FString lMSG = FString::Printf(TEXT("AnimSelected: %s, with that angle %f"), *lMontageLayerName.ToString(), lAngle);
		GEngine->AddOnScreenDebugMessage(2, 4, FColor::Blue, lMSG);
	}

}

void AYBEnemy::TakeHit(const FVector& ImpactPoint, const APawn* Causer)
{
	FVector lNormal = FVector();

	TakeHit(ImpactPoint, lNormal, Causer);
}

void AYBEnemy::TakeHit(const FVector& ImpactPoint, const FVector& Normal, const APawn* Causer)
{
	ComputeHitReactionAngle(ImpactPoint, Causer);

	//From Interface HitInterface
	Execute_OnHit(this, ImpactPoint, Causer);
}

void AYBEnemy::OnHit_Implementation(const FVector& ImpactPoint, const APawn* Causer)
{
}

float AYBEnemy::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	m_healthComponent->GiveDamage(DamageAmount);
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
