// Copyright (C) 2023 Enguerran Cobert. All Rights Reserved. Personal project based on the comics Yojimbot, this project does not have to be a commercial project.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class YOJIMBOT_UE_API SYBSlateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SYBSlateWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
