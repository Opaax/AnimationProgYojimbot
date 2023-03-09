#pragma once

UENUM(BlueprintType)
enum class EComboState : uint8
{
	ECS_OnWaiting UMETA(DisplayName = "OnWaiting"),
	ECS_OnAttack UMETA(DisplayName = "OnAttack"),
	ECS_OnAttackWindow UMETA(DisplayName = "OnAttackWindow")
};
