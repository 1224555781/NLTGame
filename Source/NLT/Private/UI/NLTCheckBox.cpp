// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NLTCheckBox.h"

#include "Core/NLTLog.h"

UNLTCheckBox::UNLTCheckBox(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

TSharedRef<SWidget> UNLTCheckBox::RebuildWidget()
{
	MyCheckbox = SNew(SCheckBox)
        .OnCheckStateChanged( BIND_UOBJECT_DELEGATE(FOnCheckStateChanged, MLB_SlateOnCheckStateChangedCallback) )
        .Style(&WidgetStyle)
        .HAlign( HorizontalAlignment )
        .ClickMethod(ClickMethod)
        .TouchMethod(TouchMethod)
        .PressMethod(PressMethod)
        .IsFocusable(IsFocusable)
        ;

	if ( GetChildrenCount() > 0 )
	{
		MyCheckbox->SetContent(GetContentSlot()->Content ? GetContentSlot()->Content->TakeWidget() : SNullWidget::NullWidget);
	}
	
	return MyCheckbox.ToSharedRef();
}

void UNLTCheckBox::MLB_SlateOnCheckStateChangedCallback(ECheckBoxState CheckBoxState)
{
	OnCheckStatChanged.Execute(CheckBoxState);
	print(TEXT("CheckStat : ") + UEnum::GetValueAsString<ECheckBoxState>(CheckBoxState));
}

void UNLTCheckBox::SetEventDelegate(const AnyType& event)
{
	if (event.IsSameType<FCheckBoxStatChanged>())
		OnCheckStatChanged = event.AnyCast<FCheckBoxStatChanged>();
	else
		MLBUILog(TEXT("event.IsSameType<FCheckBoxStatChanged>() == false") ,false,ELogVerbosity::Error);
	
}


