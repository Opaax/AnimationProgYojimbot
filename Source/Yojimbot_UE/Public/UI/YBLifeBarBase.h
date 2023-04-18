// Copyright (C) 2023 Enguerran Cobert. All Rights Reserved. Personal project based on the comics Yojimbot, this project does not have to be a commercial project.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YBLifeBarBase.generated.h"

class UYBDamageableBar;
class UOverlay;

/**
 * Base class for Life bar
 */
UCLASS()
class YOJIMBOT_UE_API UYBLifeBarBase : public UUserWidget
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
};
