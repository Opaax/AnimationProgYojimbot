

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YBPlayerOverlay.generated.h"

//FORWARD

class UCanvasPanel;

/**
 * Default YB Player overlay 
 */
UCLASS()
class YOJIMBOT_UE_API UYBPlayerOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Canvas", BindWidget = "Canvas"))
	TObjectPtr<UCanvasPanel > m_canvas;
};
