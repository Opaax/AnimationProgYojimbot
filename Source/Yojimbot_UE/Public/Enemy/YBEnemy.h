// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../DamageSystem/HitInterface.h"
#include "YBEnemy.generated.h"

class UAnimMontage;

UCLASS()
class YOJIMBOT_UE_API AYBEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYBEnemy();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Animation/Hit", meta = (DisplayName = "HitReactionMontage"))
	UAnimMontage* m_hitReactionMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animation/Hit", meta = (DisplayName = "HitForwardLayerName"))
	FName m_hitForwardLayerName = "Forward";

	UPROPERTY(EditDefaultsOnly, Category = "Animation/Hit", meta = (DisplayName = "HitBackwardLayerName"))
	FName m_hitBackwardLayerName = "Backward";

	UPROPERTY(EditDefaultsOnly, Category = "Animation/Hit", meta = (DisplayName = "HitLeftLayerName"))
	FName m_hitLeftLayerName = "Left";
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation/Hit", meta = (DisplayName = "HitForwardLayerName"))
	FName m_hitRightLayerName = "Right";

	UFUNCTION()
	void InitMeshCollision();

/// ///////////////// OVERRIDES ////////////////////////
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Inherited from IHitInterface
	virtual void TakeHit(const FVector& ImpactPoint) override;
};
