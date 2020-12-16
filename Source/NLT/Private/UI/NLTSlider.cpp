// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NLTSlider.h"


#include "Core/NLTLog.h"
#include "Widgets/Input/SSlider.h"

UNLTSlider::UNLTSlider(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UNLTSlider::SetEventDelegate(const AnyType& event)
{
	if (event.IsSameType<FSliderStatChanged>())
		SliderStatChanged = event.AnyCast<FSliderStatChanged>();
	else
		MLBUILog(TEXT("SliderStatChanged = event.AnyCast<FSliderStatChanged>() == false"),false,ELogVerbosity::Error);
}

TSharedRef<SWidget> UNLTSlider::RebuildWidget()
{
	MySlider = SNew(SSlider)
        .Style(&WidgetStyle)
        .IsFocusable(IsFocusable)
        .OnMouseCaptureBegin(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnMouseCaptureBegin))
        .OnMouseCaptureEnd(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnMouseCaptureEnd))
        .OnControllerCaptureBegin(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnControllerCaptureBegin))
        .OnControllerCaptureEnd(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnControllerCaptureEnd))
        .OnValueChanged(SliderStatChanged);

	return MySlider.ToSharedRef();
}
