#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_SPHERE_AT(Location, Duration) if(GetWorld())\
{\
	DrawDebugSphere(GetWorld(),Location,20.f,12,FColor::Red, false, Duration, 0U, 1.f);\
}