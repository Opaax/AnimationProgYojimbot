// Copyright (C) 2023 Enguerran Cobert. All Rights Reserved. Personal project based on the comics Yojimbot, this project does not have to be a commercial project.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/YBEnemy.h"
#include "YBSimpleEnemy.generated.h"

/**
 * 
 */
UCLASS()
class YOJIMBOT_UE_API AYBSimpleEnemy : public AYBEnemy
{
	GENERATED_BODY()
	
	/******************************** MEMBERS ********************************/
protected:

	/******************************** FUNCTIONS ********************************/
protected:

	/******************************** OVERRIDE ********************************/
protected:

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void TakeHit(const FVector& ImpactPoint, const APawn* Causer) override;
	virtual void TakeHit(const FVector& ImpactPoint, const FVector& Normal, const APawn* Causer) override;

	virtual void OnHit_Implementation(const FVector& ImpactPoint, const APawn* Causer) override;
};
