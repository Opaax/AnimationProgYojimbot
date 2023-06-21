// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/YBBTTask_RotateHeadToTargetActor.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "../../../Public/AI/YBAICharacter.h"
#include "../../../Public/Utils/CustomDebugMacro.h"

UYBBTTask_RotateHeadToTargetActor::UYBBTTask_RotateHeadToTargetActor(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("RotateHeadToTargetActor");

	/*Filter to accept Rotator Only*/
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UYBBTTask_RotateHeadToTargetActor, BlackboardKey),AActor::StaticClass());
}

EBTNodeResult::Type UYBBTTask_RotateHeadToTargetActor::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//Make sure The controlled pawn is YBAIChacracter
	if (AYBAICharacter* lCharacter = CastChecked<AYBAICharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		//Check if Key object is null
		if (const AActor* lTargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName)))
		{
			//Compute the rotation between target and Control Pawn
			FRotator lRotatorToTarget = UKismetMathLibrary::FindLookAtRotation(lCharacter->GetActorLocation(), lTargetActor->GetActorLocation());

			//Set pawn value if Yaw Rotate is True
			if (bRotateYaw)
			{
				lCharacter->SetYawRotationAngleToTarget(FMath::Clamp(lRotatorToTarget.Yaw, m_minYAW, m_maxYAW));
			}

			//Set pawn value if Pitch Rotate is True
			if (bRotatePitch)
			{
				lCharacter->SetPitchRotationAngleToTarget(FMath::Clamp(lRotatorToTarget.Pitch, m_minPitch, m_maxPitch));
			}

			return EBTNodeResult::Succeeded;
		}

		DEBUG_ERROR(TEXT("%s, Blackboard Object is nullptr"), *this->GetName());

		return EBTNodeResult::Failed;
	}

	DEBUG_ERROR(TEXT("%s, This task is made for YB AI Character, your Pawn must be inherited from AYBAICharacter"), *this->GetName());

	return EBTNodeResult::Failed;
}

FString UYBBTTask_RotateHeadToTargetActor::GetStaticDescription() const
{
	if(!BlackboardKey.SelectedKeyName.IsNone())
	{
		return FString::Printf(TEXT("RotatorKey: %s"), *BlackboardKey.SelectedKeyName.ToString());
	}
		
	return Super::GetStaticDescription();
}
