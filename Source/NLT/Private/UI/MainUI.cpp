// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Core/NLTLog.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ParticalWidget.h"

UMainUI::UMainUI(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    //WidgetTree->RootWidget = WidgetTree->ConstructWidget<UPanelWidget>(UPanelWidget::StaticClass(),FName(TEXT("CavasPanel")));
}

void UMainUI::NativePreConstruct()
{
    Super::NativePreConstruct();
    /*if ( WidgetTree->RootWidget == nullptr)
    {
        RootWidgetS =WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(),FName(TEXT("CanvasRoot")));
        WidgetTree->RootWidget = RootWidgetS;
    }
    if (WidgetTree)// && WidgetTree->RootWidget)
    {
        WidgetSwitcher = WidgetTree->ConstructWidget<UWidgetSwitcher>(UWidgetSwitcher::StaticClass(),FName(TEXT("WidgetSwitcher")));
        UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(WidgetSwitcher->Slot);
        if (ParentSlot)
        {
            FAnchorData Data;
            Data.Anchors = FAnchors(0.f,0.f,1.f,1.f);
            Data.Alignment = FVector2D();
            Data.Offsets = FMargin();
            
            ParentSlot->SetLayout(Data);
        }
        auto b = WidgetTree->ConstructWidget<UButton>();
        UCanvasPanel* ROOT = Cast<UCanvasPanel>(WidgetTree->RootWidget);
        ROOT->AddChild(WidgetSwitcher);
        ROOT->AddChild(b);
        
        print(TEXT("WidgetSwitcher Create Success"));
    }
    else
    {
        print(TEXT("WidgetSwitcher Create Failed"));
    }*/
    
}

void UMainUI::NativeConstruct()
{
    Super::NativeConstruct();

    
}

TSharedRef<SWidget> UMainUI::RebuildWidget()
{
   
    if ( WidgetTree->RootWidget == nullptr)
    {
        RootWidgetS =WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(),FName(TEXT("CanvasRoot")));
        WidgetTree->RootWidget = RootWidgetS;
    }
   
    TSharedRef<SWidget> widget = Super::RebuildWidget();
    
    if (WidgetTree)// && WidgetTree->RootWidget)
        {
        WidgetSwitcher = WidgetTree->ConstructWidget<UWidgetSwitcher>(UWidgetSwitcher::StaticClass(),FName(TEXT("WidgetSwitcher")));
        
        auto b = WidgetTree->ConstructWidget<UButton>();
        UCanvasPanel* ROOT = Cast<UCanvasPanel>(WidgetTree->RootWidget);
        ROOT->AddChild(WidgetSwitcher);
        ROOT->AddChild(b);
        UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(WidgetSwitcher->Slot);
        if (ParentSlot)
        {
            FAnchorData Data;
            Data.Anchors = FAnchors(0.f,0.f,1.f,1.f);
            Data.Alignment = FVector2D();
            Data.Offsets = FMargin();
            
            ParentSlot->SetLayout(Data);
        }
        print(TEXT("WidgetSwitcher Create Success"));
        }
    else
    {
        print(TEXT("WidgetSwitcher Create Failed"));
    }

    return widget;
}

bool UMainUI::Initialize()
{
   bool t = Super::Initialize();
    /*UPanelWidget* RootWidget =Cast<UPanelWidget>( GetRootWidget());
    if (WidgetTree && RootWidget)
    {
        WidgetSwitcher = WidgetTree->ConstructWidget<UWidgetSwitcher>(UWidgetSwitcher::StaticClass());
        print(TEXT("WidgetSwitcher Create Success"));
        RootWidget->AddChild(WidgetSwitcher);
        // WidgetTree->RootWidget.
    }
    else
    {
        print(TEXT("WidgetSwitcher Create Failed"));
    }*/
   return t;
  
}

void UMainUI::SetContentForSlot(FName SlotName, UWidget* Content)
{
    Super::SetContentForSlot(SlotName, Content);
    
}

void UMainUI::SwtichUI(int8 ActiveIndex)
{
    WidgetSwitcher->ActiveWidgetIndex = ActiveIndex;
}

void UMainUI::SwtichUI(UWidget* ActiveWidget)
{
    WidgetSwitcher->SetActiveWidget(ActiveWidget);
}
