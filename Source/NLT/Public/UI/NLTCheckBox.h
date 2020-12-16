// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CheckBox.h"
#include "Core/NLTDataTypes.h"
#include "RTTI/AnyType.h"
#include "NLTCheckBox.generated.h"


/**
 * 
 */
UCLASS(meta=( DisplayName="CheckBox (NLT)"))
class NLT_API UNLTCheckBox : public UCheckBox
{
	GENERATED_UCLASS_BODY()
	public:
	//UNLTCheckBox(const FObjectInitializer& Initializer);

	public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	void MLB_SlateOnCheckStateChangedCallback(ECheckBoxState CheckBoxState);

	void SetEventDelegate(const AnyType& event);
	FCheckBoxStatChanged OnCheckStatChanged;
};
