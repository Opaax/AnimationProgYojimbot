// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/YBEnemyLifeBar.h"
#include "Components/ProgressBar.h"
#include "Components/Overlay.h"
#include "../../Public/UI/YBDamageableBar.h"

void UYBEnemyLifeBar::InitializeValues(const float MaxLife, const float CurrentLife)
{
	m_maxLife = MaxLife;
	m_currentLife = CurrentLife;

	const float lRatio = m_currentLife / m_maxLife;

	if (LifeBar)
	{
		LifeBar->SetInitialeProgressValues(lRatio, 1.f);
	}
}

void UYBEnemyLifeBar::UpdateLife(const float NextLife, const float LifeRatio)
{
	m_currentLife = NextLife;

	LifeBar->SetTopProgress(LifeRatio);
}


