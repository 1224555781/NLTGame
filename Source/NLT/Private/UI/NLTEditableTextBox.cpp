// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NLTEditableTextBox.h"

#include "Core/NLTLog.h"

UNLTEditableTextBox::UNLTEditableTextBox(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
}

void UNLTEditableTextBox::SetEventDelegate(const AnyType& event)
{
	if (event.IsSameType<FEditableTextStatChanged>())
		EditableTextStatChanged = event.AnyCast<FEditableTextStatChanged>();
	else
		MLBUILog(TEXT("EditableTextStatChanged = event.AnyCast<FEditableTextStatChanged>() == false"),false,ELogVerbosity::Error);
}

void UNLTEditableTextBox::HandleOnTextCommitted(const FText& InText, ETextCommit::Type CommitMethod)
{
	Super::HandleOnTextCommitted(InText, CommitMethod);
	EditableTextStatChanged.Execute(InText,CommitMethod);
}

void UNLTEditableTextBox::HandleOnTextChanged(const FText& InText)
{
	Super::HandleOnTextChanged(InText);
	EditableTextStatChanged.Execute(InText,ETextCommit::Default);
}
