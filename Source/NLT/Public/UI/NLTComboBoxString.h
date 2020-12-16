// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ComboBoxString.h"
#include "Core/NLTDataTypes.h"
#include "RTTI/AnyType.h"

#include "NLTComboBoxString.generated.h"

/**
 * 
 */
UCLASS(meta=( DisplayName="ComboBox (NLT)"))
class NLT_API UNLTComboBoxString : public UComboBoxString
{
	GENERATED_UCLASS_BODY()
	public:
	//UNLTComboBoxString(const FObjectInitializer& Initializer);

	public:
	void SetEventDelegate(const AnyType& event);
	FComboBoxStatChanged ComboBoxStatChanged;
	virtual void HandleSelectionChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectionType)override;

	
};
