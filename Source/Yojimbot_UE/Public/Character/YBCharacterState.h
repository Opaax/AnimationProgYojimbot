#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unarmed UMETA(DisplayName = "Unarmed"),
	ECS_OneHandWeapon UMETA(DisplayName = "OneHandWeapon")
};

UENUM(BlueprintType)
enum class ECharacterActionState : uint8
{
	ECAS_Unoccupied UMETA(DisplayName = "UnOccupied"),
	ECAS_Attacking UMETA(DisplayName = "Attacking"),
	ECAS_AttackComboTransition UMETA(DisplayName = "AttackComboTransition")
};
