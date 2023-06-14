

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YBPlayerOverlay.generated.h"

//FORWARD

class UCanvasPanel;
class UYBPlayerLifeBar;

/**
 * Default YB Player overlay 
 */
UCLASS()
class YOJIMBOT_UE_API UYBPlayerOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BindWidget))
	TObjectPtr<UYBPlayerLifeBar> LifeBar;
};
