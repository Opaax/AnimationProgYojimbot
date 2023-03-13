// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YBDamageableBar.generated.h"

class UMaterialInstanceDynamic;
class UMaterialInstance;
class UImage;
class UOverlay;
class USizeBox;

/**
 * 
 */
UCLASS()
class YOJIMBOT_UE_API UYBDamageableBar : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damageable, meta = (DisplayName = "DamageableMaterial"))
	TObjectPtr<UMaterialInstance> m_damageableMaterial;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Damageable, meta = (DisplayName = "DamageableMaterialInstanceDynamic"))
	TObjectPtr<UMaterialInstanceDynamic> m_damageableInstMatDyn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damageable, meta = (DisplayName = "TopProgressParameterName"))
	FName m_topProgressParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damageable, meta = (DisplayName = "BottomProgressParameterName"))
	FName m_bottomProgressParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Damageable, meta = (DisplayName = "AnimationSpeed"))
	float m_animationSpeed = 10.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, BlueprintSetter = SetTopProgress)
	float m_topProgress;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	float m_bottomProgress;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	float m_prevTopProgress;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (BindWidget))
	TObjectPtr<UImage> HealthImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (BindWidget))
	TObjectPtr<UOverlay> OverlayContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBoxBar;

protected:

	UFUNCTION(BlueprintCallable)
	void SetImageMaterial();

	UFUNCTION(BlueprintCallable)
	void AnimLifeBar(const float DeltaTime);

public:

	UFUNCTION(BlueprintCallable)
	void SetBarMaterialParameters(const float TopProgress, const float BottomProgress);

	UFUNCTION(BlueprintCallable)
	void SetInitialeProgressValues(const float TopProgress, const float BottomProgress);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetTopProgress(const float NextProgress) { m_topProgress = NextProgress; }

/////////////// OVERRIDE ////////////
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

};
