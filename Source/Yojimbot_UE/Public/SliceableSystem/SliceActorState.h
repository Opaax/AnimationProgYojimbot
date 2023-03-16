#pragma once

UENUM(BlueprintType)
enum class ESliceActorState : uint8
{
	ESAS_OnWaiting UMETA(DisplayName = "OnWaiting"),
	ESAS_OnSlice UMETA(DisplayName = "OnSlice"),
	ESAS_OnDisappear UMETA(DisplayName = "OnSlice")
};