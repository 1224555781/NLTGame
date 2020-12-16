// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParticalWidget.h"

UParticalWidget::UParticalWidget(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    LineHeight = 0.f;
    ID = NAME_None;
    Caption = FText();
    
}

void UParticalWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (LineHeight > 0)
    {
        
    }
}
