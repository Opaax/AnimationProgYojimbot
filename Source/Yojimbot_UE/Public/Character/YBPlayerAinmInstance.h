// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterState.h"
#include "YBPlayerAinmInstance.generated.h"

class AYBPlayerCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class YOJIMBOT_UE_API UYBPlayerAinmInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Refs")
	AYBPlayerCharacter* m_playerCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Refs")
	UCharacterMovementComponent* m_characterMovement = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bIsFalling = false;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bUseRootMotion = false;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float m_groundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	FVector2D m_inputDirection;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ECharacterState m_currentCharacterState;
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void GetPlayerCharacter();

	UFUNCTION(BlueprintCallable)
	void GetPlayerGroundSpeed();

	UFUNCTION(BlueprintCallable)
	void GetPlayerFallingState();

	UFUNCTION(BlueprintCallable)
	void GetPlayerCharacterState();

	UFUNCTION(BlueprintCallable)
	void GetPlayerUseRootMotion();

	UFUNCTION(BlueprintCallable)
	void GetPlayerInputDirection();
};
