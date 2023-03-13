// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YBEnemyLifeBar.generated.h"

class UYBDamageableBar;
class UOverlay;

UCLASS()
class YOJIMBOT_UE_API UYBEnemyLifeBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Life)
	float m_maxLife = 100;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Life)
	float m_currentLife = 100;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	TObjectPtr<UYBDamageableBar> LifeBar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	TObjectPtr<UOverlay> OverlayContainer;

protected:

public:
	UFUNCTION(BlueprintCallable)
	void InitializeValues(const float MaxLife, const float CurrentLife);


	/// <summary>
	/// update intern params
	/// </summary>
	/// <param name="NextLife">The next current life </param>
	/// <param name="LifeRatio">value between 0-1</param>
	UFUNCTION(BlueprintCallable)
	void UpdateLife(const float NextLife, const float LifeRatio);

//////////// OVERRIDE //////////////
protected:
};
