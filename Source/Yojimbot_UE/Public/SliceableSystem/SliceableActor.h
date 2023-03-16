// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SliceActorState.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slice/Setting", meta = (DisplayName = "SliceFrequency"))
	float m_sliceFrequency = .3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slice/Setting", meta = (DisplayName = "MaxSlice"))
	int32 m_maxSlice = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slice", meta = (DisplayName = "SliceState"))
	ESliceActorState m_sliceState = ESliceActorState::ESAS_OnWaiting;

	UPROPERTY(VisibleAnywhere, Category = "Slice/Runtime")
	TArray<UProceduralMeshComponent*> m_slicedComp;

	UPROPERTY(VisibleAnywhere, Category = "Slice/Runtime")
	int32 m_sliceCount;

	FTimerHandle SliceFrequencyTimerHandler;

protected:

	UFUNCTION()
	void OnProceduralComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = Slice)
	void BindNewToCompToBeginOverlap(UProceduralMeshComponent* NewComp);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// Compute position and normal for the slice
	/// Call the Event OnSlice
	/// </summary>
	/// <param name="Causer">The actor cause that event call</param>
	/// <param name="OverlappedComp">the comp that received the overlap</param>
	void ProductSlice(AActor* Causer, UProceduralMeshComponent* OverlappedComp);

	UFUNCTION()
	void OnSliceEnableForNextSlice();

	UFUNCTION()
	void RefreshEventHandlerFromProcMeshComp();

public:	
	ASliceableActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Slice")
	void OnSlice(const FVector& ImpactPoint, const FVector& Normal, UProceduralMeshComponent* CompOverlapped);

	UFUNCTION()
	bool IsCanSlice();

//////////// OVERRIDE ///////////////
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
