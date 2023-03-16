// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../SliceableSystem/SlicerInterface.h"
#include "YBWeaponBase.generated.h"

class UBoxComponent;
class USceneComponent;
class UPrimitiveComponent;

UCLASS()
class YOJIMBOT_UE_API AYBWeaponBase : public AActor, public ISlicerInterface
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

	UPROPERTY(EditDefaultsOnly, Category = Collision, meta = (DisplayName = "BoxTraceHalfSize"))
	FVector m_boxTraceHalfSize = FVector(5.f, 5.f, 5.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	TArray<AActor*> m_actorToIgnoreWhileOverlaping;
protected:
	UFUNCTION()
	void OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:

	UFUNCTION(BlueprintCallable,Category = Collision)
	void ActivateAttackCollision();

	UFUNCTION(BlueprintCallable, Category = Collision)
	void DesactivateAttackCollision();


	//ISlicerInterface
	virtual FVector GetForwardFromRotation();
	virtual FVector GetUpFromRotation();

	////////// GETTER / SETTER //////////
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return m_mesh; }

	/////////// OVERRIDE /////////////
protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
public:
	virtual void Tick(float DeltaTime) override;
	/////////// END OVERRIDE ///////////
};
