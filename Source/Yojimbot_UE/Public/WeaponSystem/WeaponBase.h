// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class YOJIMBOT_UE_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();
protected:

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* m_rootComp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetMesh)
	UStaticMeshComponent* m_mesh = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return m_mesh; }
};
