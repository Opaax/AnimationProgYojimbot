// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SliceableActor.generated.h"

class UPrimitiveComponent;
class USceneComponent;
class UStaticMeshComponent;
class UProceduralMeshComponent;
class UMaterialInstance;
class UStaticMesh;

UCLASS()
class YOJIMBOT_UE_API ASliceableActor : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = Slice, meta = (DisplayName = "BaseMeshComp"))
	TObjectPtr<UStaticMeshComponent> m_baseMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = Slice, meta = (DisplayName = "ProceduralMeshComp"))
	TObjectPtr<UProceduralMeshComponent> m_meshProceduralComp;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Slice/Setting", meta = (DisplayName = "MeshToCopy"))
	TObjectPtr<UStaticMesh> m_meshToCopy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slice/Setting", meta = (DisplayName = "CapSliceMaterial"))
	TObjectPtr<UMaterialInstance> m_capSliceMaterial;

	UPROPERTY(VisibleAnywhere, Category = "Slice/Runtime")
	TArray<UProceduralMeshComponent*> m_slicedComp;

protected:

public:	
	ASliceableActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Slice")
	void OnSlice(const FVector& ImpactPoint, const FVector& Normal);

//////////// OVERRIDE ///////////////
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
