// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../DamageSystem/HitInterface.h"
#include "YBEnemy.generated.h"

class UAnimMontage;
class APawn;
class UYBHealthComponent;
class AController;
class UWidgetComponent;
class UYBEnemyLifeBar;

UCLASS()
class YOJIMBOT_UE_API AYBEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

protected:

//////////// ANIMATION ////////////////
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

//////////// END ANIMATION ////////////////

//////////// HEALTH ////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
	TSubclassOf<UYBEnemyLifeBar> m_healthWidgetCompClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Health)
	TObjectPtr<UYBEnemyLifeBar> m_healthWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = YBComponents)
	TObjectPtr<UYBHealthComponent> m_healthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , meta = (DisplayName = "LifeWidgetComp", AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> m_lifeWidgetComponent;
//////////// END HEALTH ////////////////

public:
	AYBEnemy();

protected:

	UFUNCTION()
	void InitMeshCollision();

	UFUNCTION()
	void InitHealthComponent();

	UFUNCTION(BlueprintCallable)
	void ComputeHitReactionAngle(const FVector& ImpactPoint, const APawn* Causer);

	UFUNCTION()
	void OnHealthCompUpdate(const float Currenthealth, const float HealthRatio);

//////////////////// OVERRIDES ////////////////////////
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, const FDamageEvent&  DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void TakeHit(const FVector& ImpactPoint, const APawn* Causer) override;
	virtual void TakeHit(const FVector& ImpactPoint,const FVector& Normal, const APawn* Causer) override;

	virtual void OnHit_Implementation(const FVector& ImpactPoint, const APawn* Causer) override;
};
