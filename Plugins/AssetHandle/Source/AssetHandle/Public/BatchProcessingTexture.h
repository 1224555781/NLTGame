// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BatchProcessingTexture.generated.h"

/**
 * 
 */
UCLASS()
class ASSETHANDLE_API UBatchProcessingTexture : public UObject
{
	GENERATED_BODY()


public:
   
    TSharedPtr<SEditableTextBox>EditableTextBox;
    FReply ClickedButton();
};
