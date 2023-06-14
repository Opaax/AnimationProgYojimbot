// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/YBPlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "../../Public/Framework/YBPlayerController.h"
#include "../../Public/UI/YBPlayerOverlay.h"
#include "../../Public/Utils/CustomDebugMacro.h"
#include "../../Public/Character/YBPlayerCharacter.h"
#include "../../Public/Components/YBHealthComponent.h"
#include "../../Public/UI/YBPlayerLifeBar.h"

void AYBPlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	InitWidget();
}

void AYBPlayerHUD::InitWidget()
{
	if (m_overlayWidgetClass)
	{
		if (UWorld* lWorld = GetWorld())
		{
			//We know is single player game, use index 0
			if (AYBPlayerController* lYBController = Cast<AYBPlayerController>(UGameplayStatics::GetPlayerController(lWorld, 0)))
			{
				m_currentOverlay = CreateWidget<UYBPlayerOverlay>(lYBController, m_overlayWidgetClass);
				m_currentOverlay->AddToViewport();

				if (AYBPlayerCharacter* lCharac = Cast<AYBPlayerCharacter>(lYBController->GetPawn()))
				{
					if (UYBHealthComponent* lHealthComp = lCharac->GetHealthComponent())
					{
						m_currentOverlay->LifeBar->InitializeValues(lHealthComp->GetMaxHealth(), lHealthComp->GetHealth());

						lHealthComp->OnHealthUpdate.AddDynamic(this, &AYBPlayerHUD::OnHealthCompUpdate);
					}
				}
			}
		}
	}
	else
	{
		DEBUG_ERROR(TEXT("%s, %s, %s, m_overlayWidgetClass is not set"), *CURRENT_CLASS, *CURRENT_FUNC, *CURRENT_LINE);
	}
}

void AYBPlayerHUD::OnHealthCompUpdate(float CurrentHealth, const float HealthRatio)
{
	m_currentOverlay->LifeBar->UpdateLife(CurrentHealth, HealthRatio);
}
