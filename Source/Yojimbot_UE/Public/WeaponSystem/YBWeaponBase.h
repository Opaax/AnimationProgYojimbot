// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YBWeaponBase.generated.h"

class UBoxComponent;
class USceneComponent;
class UPrimitiveComponent;

UCLASS()
class YOJIMBOT_UE_API AYBWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AYBWeaponBase();
protected:

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* m_rootComp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetMesh)
	UStaticMeshComponent* m_mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Collision, meta = (DisplayName = "AttackCollider"))
	UBoxComponent* m_attackCollision;

	UPROPERTY(EditDefaultsOnly, Category = Collision, meta = (DsiplayName = "StartTrace"))
	USceneComponent* m_startTrace;

	UPROPERTY(EditDefaultsOnly, Category = Collision, meta = (DsiplayName = "EndTrace"))
	USceneComponent* m_endTrace;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	UFUNCTION()
	void OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return m_mesh; }

	UFUNCTION(BlueprintCallable,Category = Collision)
	void ActivateAttackCollision();

	UFUNCTION(BlueprintCallable, Category = Collision)
	void DesactivateAttackCollision();
};
