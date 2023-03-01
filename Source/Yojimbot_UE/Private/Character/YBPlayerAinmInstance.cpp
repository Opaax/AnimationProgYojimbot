// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/YBPlayerAinmInstance.h"
#include "../Public/Character/YBPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UYBPlayerAinmInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	GetPlayerCharacter();
}

void UYBPlayerAinmInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	GetPlayerFallingState();
	GetPlayerGroundSpeed();
	GetPlayerInputDirection();
	GetPlayerUseRootMotion();
	GetPlayerCharacterState();
}

void UYBPlayerAinmInstance::GetPlayerCharacter()
{
	if (AYBPlayerCharacter* lCharacter = Cast<AYBPlayerCharacter>(TryGetPawnOwner()))
	{
		m_playerCharacter = lCharacter;
		m_characterMovement = lCharacter->GetCharacterMovement();
	}
}

void UYBPlayerAinmInstance::GetPlayerGroundSpeed()
{
	if (m_playerCharacter != nullptr)
	{
		m_groundSpeed = UKismetMathLibrary::VSizeXY(m_playerCharacter->GetCharacterMovement()->Velocity);
	}
}

void UYBPlayerAinmInstance::GetPlayerFallingState()
{
	if (m_playerCharacter != nullptr)
	{
		bIsFalling = m_characterMovement->IsFalling();
	}
}

void UYBPlayerAinmInstance::GetPlayerCharacterState()
{
	if (m_playerCharacter != nullptr)
	{
		m_currentCharacterState = m_playerCharacter->GetCurrentState();
	}
}

void UYBPlayerAinmInstance::GetPlayerUseRootMotion()
{
	if (m_playerCharacter != nullptr)
	{
		bUseRootMotion = m_playerCharacter->GetUseRootMotion();
	}
}

void UYBPlayerAinmInstance::GetPlayerInputDirection()
{
	if (m_playerCharacter != nullptr)
	{
		m_inputDirection = m_playerCharacter->GetInputDirection();
	}
}