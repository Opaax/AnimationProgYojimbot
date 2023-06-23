// Copyright (C) 2023 Enguerran Cobert. All Rights Reserved. Personal project based on the comics Yojimbot, this project does not have to be a commercial project.


#include "Enemy/YBSimpleEnemy.h"

void AYBSimpleEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void AYBSimpleEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AYBSimpleEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AYBSimpleEnemy::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator,DamageCauser);
}

void AYBSimpleEnemy::TakeHit(const FVector& ImpactPoint, const APawn* Causer)
{
    Super::TakeHit(ImpactPoint, Causer);
}

void AYBSimpleEnemy::TakeHit(const FVector& ImpactPoint, const FVector& Normal, const APawn* Causer)
{
    Super::TakeHit(ImpactPoint, Normal, Causer);
}

void AYBSimpleEnemy::OnHit_Implementation(const FVector& ImpactPoint, const APawn* Causer)
{

}
