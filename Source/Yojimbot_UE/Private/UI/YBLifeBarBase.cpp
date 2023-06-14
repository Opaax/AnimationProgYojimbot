// Copyright (C) 2023 Enguerran Cobert. All Rights Reserved. Personal project based on the comics Yojimbot, this project does not have to be a commercial project.


#include "UI/YBLifeBarBase.h"
#include "Components/ProgressBar.h"
#include "Components/Overlay.h"
#include "../../Public/UI/YBDamageableBar.h"

void UYBLifeBarBase::InitializeValues(const float MaxLife, const float CurrentLife)
{
	m_maxLife = MaxLife;
	m_currentLife = CurrentLife;

	const float lRatio = m_currentLife / m_maxLife;

	if (LifeBar)
	{
		LifeBar->SetInitialProgressValues(lRatio, 1.f);
	}
}

void UYBLifeBarBase::UpdateLife(const float NextLife, const float LifeRatio)
{
	m_currentLife = NextLife;

	LifeBar->SetTopProgress(LifeRatio);
}

