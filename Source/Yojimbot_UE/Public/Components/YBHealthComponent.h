// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YBHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdate, const float, CurrentHealth, const float, HealthRatio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YOJIMBOT_UE_API UYBHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintGetter = GetHealth, BlueprintSetter = SetHealth, meta = (DisplayName = "Health"))
	float m_health;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetMaxHealth,  meta = (DisplayName = "MaxHealth"))
	float m_maxHealth;

public:

	UPROPERTY(BlueprintAssignable, Category = Callback)
	FOnHealthUpdate OnHealthUpdate;

public:	
	UYBHealthComponent();

	UFUNCTION()
	void GiveDamage(const float Damage);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float GetHealth() const { return m_health; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float GetMaxHealth() const { return m_maxHealth; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetHealth(float NewHealth) { m_health = NewHealth; OnHealthUpdate.Broadcast(GetHealth(), GetHealthRatio()); }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE float GetHealthRatio() const { return m_health / m_maxHealth; }

///////////////// OVERRIDES ///////////////////
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
