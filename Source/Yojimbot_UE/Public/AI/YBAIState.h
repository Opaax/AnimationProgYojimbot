#pragma once

UENUM(BlueprintType)
enum class EAIState : uint8
{
	EAIS_Dummy UMETA(DisplayName = "Dummy"),
	EAIS_Patrolling UMETA(DisplayName = "Patrolling"),
	EAIS_Combat UMETA(DisplayName = "Combat")
};