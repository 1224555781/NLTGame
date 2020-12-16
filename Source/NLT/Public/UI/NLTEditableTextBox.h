// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableTextBox.h"
#include "Core/NLTDataTypes.h"
#include "RTTI/AnyType.h"

#include "NLTEditableTextBox.generated.h"

/**
 * 
 */
UCLASS(meta=( DisplayName="EditableTextBox (NLT)"))
class NLT_API UNLTEditableTextBox : public UEditableTextBox
{
	GENERATED_UCLASS_BODY()
	public:
	//UNLTEditableTextBox(const FObjectInitializer& Initializer);

	public:
	void SetEventDelegate(const AnyType& event);
	FEditableTextStatChanged EditableTextStatChanged;
	virtual void HandleOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)override;

	virtual void HandleOnTextChanged(const FText& Text)override;
};
