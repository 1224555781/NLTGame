// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NLTComboBoxString.h"

#include "Core/NLTLog.h"

UNLTComboBoxString::UNLTComboBoxString(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
}

void UNLTComboBoxString::SetEventDelegate(const AnyType& event)
{
	if (event.IsSameType<FComboBoxStatChanged>())
		ComboBoxStatChanged = event.AnyCast<FComboBoxStatChanged>();
	else
		MLBUILog(TEXT("ComboBoxStatChanged = event.AnyCast<FComboBoxStatChanged>() == false"),false,ELogVerbosity::Error);
}

void UNLTComboBoxString::HandleSelectionChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectionType)
{
	Super::HandleSelectionChanged(Item, SelectionType);
	if ( !IsDesignTime() )
		ComboBoxStatChanged.Execute(Item.IsValid() ? *Item : FString(),SelectionType);
}
