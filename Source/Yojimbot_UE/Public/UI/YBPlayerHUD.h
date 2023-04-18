// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/YBHUD.h"
#include "YBPlayerHUD.generated.h"

//FORWARD
class UYBPlayerOverlay;

/**
 * Player HUD.
 */
UCLASS()
class YOJIMBOT_UE_API AYBPlayerHUD : public AYBHUD
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = Widget, meta = (DisplayName = "OverlayWidgetClass"))
	TSubclassOf<UYBPlayerOverlay> m_overlayWidgetClass;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetCurrentOverlay, Category = Overlay, meta = (DisplayName = "CurrentOverlay"))
	TObjectPtr<UYBPlayerOverlay> m_currentOverlay;

protected: 

	/*
	* Create a widget based on 'm_overlayWidgetClass'
	**/
	UFUNCTION()
	virtual void InitWidget();

public:
	//////// GETTER / SETTER ///////
	UFUNCTION(BlueprintPure, BlueprintCallable)
	FORCEINLINE UYBPlayerOverlay* GetCurrentOverlay() { return m_currentOverlay; }
	
	/////// OVERRIDE ////////
public:

	void BeginPlay() override;

};
