#pragma once

#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

/////////// DRAW //////////////
#define DRAW_SPHERE_AT(Location, Duration) if(GetWorld())\
{\
	DrawDebugSphere(GetWorld(),Location,20.f,12,FColor::Red, false, Duration, 0U, 1.f);\
}

#define DRAW_ARROW(Start, End, Color) if(GetWorld())\
{\
	UKismetSystemLibrary::DrawDebugArrow(GetWorld(),Start,End, 2.f,Color, 5.f, 4.f);\
}

//////////// LOG ///////////////////
#define DEBUG_ERROR(...) UE_LOG(LogTemp,Error,__VA_ARGS__)
#define DEBUG_WARNING(...) UE_LOG(LogTemp,Warning,__VA_ARGS__)
#define DEBUG_LOG(...) UE_LOG(LogTemp,Log,__VA_ARGS__)