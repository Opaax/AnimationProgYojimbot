// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/YBDamageableBar.h"

#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"

void UYBDamageableBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetImageMaterial();
}

void UYBDamageableBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UYBDamageableBar::NativeDestruct()
{
	Super::NativeDestruct();
}

void UYBDamageableBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	AnimLifeBar(InDeltaTime);
}

void UYBDamageableBar::SetBarMaterialParameters(const float TopProgress, const float BottomProgress)
{
	//Debug message
	if (m_topProgressParameterName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("TopProgressParameterName as NONE in %s %s"),*GetName(), *FString("SetBarMaterialParameters"));
	}
	if (m_bottomProgressParameterName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("BottomProgressParameterName as NONE in %s %s"), *GetName(), *FString("SetBarMaterialParameters"));
	}

	//Set value into material
	if (m_damageableInstMatDyn)
	{
		m_damageableInstMatDyn->SetScalarParameterValue(m_topProgressParameterName, TopProgress);
		m_damageableInstMatDyn->SetScalarParameterValue(m_bottomProgressParameterName, BottomProgress);
	}
}

void UYBDamageableBar::SetInitialeProgressValues(const float TopProgress, const float BottomProgress)
{
	m_bottomProgress = BottomProgress;
	m_topProgress = m_prevTopProgress = TopProgress;
}

void UYBDamageableBar::SetImageMaterial()
{
	if (m_damageableMaterial != nullptr)
	{
		m_damageableInstMatDyn = UMaterialInstanceDynamic::Create(m_damageableMaterial, this);
		
		HealthImage->SetBrushFromMaterial(m_damageableInstMatDyn);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Material"));
	}
}

void UYBDamageableBar::AnimLifeBar(const float DeltaTime)
{
	//diff between prev/top progress
	//make it neg
	m_bottomProgress += (m_topProgress - m_prevTopProgress) * -1.f;
	m_bottomProgress -= DeltaTime * m_animationSpeed;

	//make sure to not be under 0 and upper 1
	m_bottomProgress = FMath::Clamp(m_bottomProgress, 0.f,1.f);

	//prev set as current since math has been done
	m_prevTopProgress = m_topProgress;

	//Update material
	SetBarMaterialParameters(m_topProgress, m_bottomProgress);
}