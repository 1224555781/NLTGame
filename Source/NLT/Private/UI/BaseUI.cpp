// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseUI.h"


#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Core/NLTLog.h"
#include "Core/NLTUICore.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/UIBuildHelpFunctionLibrary.h"


UBaseUI::UBaseUI(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    
}

void UBaseUI::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    //UICore = UUIBuildHelpFunctionLibrary::GetUICore(this);
   
}

void UBaseUI::NativePreConstruct()
{
    Super::NativePreConstruct();
 
    
}

void UBaseUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (ContentBox)
    {
        UICore = UUIBuildHelpFunctionLibrary::GetUICore(this);
        BuildColumn();
        SetScaleInScreen(FVector2D(Info.Width,Info.Height));
        UCanvasPanelSlot* MenuVSlot= Cast<UCanvasPanelSlot>( MenuVerticalBox->Slot);
        MenuVSlot->SetOffsets(Info.Padding);
        SetBackGroundImage(Info.BackgroundTexture);
    }
}

void UBaseUI::BuildColumn()
{
    switch (Info.UIColumn)
    {
    case Column_One:
        CreateColumn(0.f);
        break;
    case Column_Two:
        CreateColumn(0.f);
        CreateColumn(Info.ColumnDistance);
        break;
    case Column_Three:
        CreateColumn(0.f,1.f);
        CreateColumn(Info.ColumnDistance,2.f);
        break;
    case Column_Four:
        CreateColumn(0.f,2.f);
        CreateColumn(Info.ColumnDistance);break;
    case Column_Five:
        CreateColumn(0.f);
        CreateColumn(Info.ColumnDistance);
        CreateColumn(Info.ColumnDistance);break;
       
    default: ;
    }
    
}

void UBaseUI::CreateColumn(float ColumnDistance, float Width)
{
    if (ColumnDistance > 0)
    {
        const auto* m= UICore->ChildWidgets.Find(EWidgetType::Spacer);
        if (m && *m)
        {
            UWidget* SpaceWidget = CreateWidget(this,*m);
            
            auto*Conten = ContentBox->AddChildToHorizontalBox(SpaceWidget);
            Conten->SetPadding(FMargin( ColumnDistance,0.f,0.f,0.f));
        }
    }
    const auto* menuclass= UICore->ChildWidgets.Find(EWidgetType::Menu);
    if (menuclass && *menuclass)
    {
        UWidget* MenuWidget = CreateWidget(this,*menuclass);
        AllMenuWidget.Add(static_cast<TArray<UParticalWidget*>::ElementType>(MenuWidget));
        auto*Conten = ContentBox->AddChildToHorizontalBox(MenuWidget);
        auto size =  FSlateChildSize(ESlateSizeRule::Fill);
        size.Value = Width;
        Conten->SetSize(size);
        auto m = Cast<UCanvasPanelSlot>(MenuVerticalBox->Slot);
        m->SetOffsets(Info.Padding);
    }
    ElementCounts.Add(0);
}

void UBaseUI::SetScaleInScreen(FVector2D ScaleSize)
{
    FVector2D Size =  ScaleSize.ClampAxes(0,1);
    FVector2D ScreenSize =  UWidgetLayoutLibrary::GetViewportSize(this);
    FVector2D ResultSize = FVector2D(Size.X * ScreenSize.X,Size.Y * ScreenSize.Y) / UWidgetLayoutLibrary::GetViewportScale(this);
    auto m = Cast<UCanvasPanelSlot>(MenuContenBox->Slot);
    m->SetSize(ResultSize);
}

void UBaseUI::SetBackGroundImage(UTexture* BackGround)
{
    if(!BackGround)
        return;
    //首先判断添加样式风格
    //后续添加

    //



    FSlateBrush Brush;
    Brush.SetImageSize(FVector2D(32.f));
    Brush.SetResourceObject( BackGround);
    BGImage->SetBrush(Brush);
    BGImage->SetVisibility(ESlateVisibility::Visible);
    
    if(Info.bShowDarkBG)
    {
        DarkBGImage->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        DarkBGImage->SetVisibility(ESlateVisibility::Collapsed);
    }
    
}

UPanelSlot* UBaseUI::AddElement(UParticalWidget* ParticalWidget, EVerticalAlignment VerticalAlignment)
{
    RegisterElement(ParticalWidget);
    switch (VerticalAlignment)
    {
    case VAlign_Fill: break;
    case VAlign_Top:
        return HeaderVerticalBox->AddChild(ParticalWidget);
        break;
    case VAlign_Center:
        UVerticalBox* V;
        GetMenuWidget()->Execute_GetMenuVerticalWidget(GetMenuWidget(),V);
        //单纯添加一个空格不要增加计数
        if (ParticalWidget->WidgetType!=EWidgetType::Spacer)
            ElementCounts[CurrentMenuWidget] = ++ElementCounts[CurrentMenuWidget];
        if (V)
            return V->AddChild(ParticalWidget);
        else
            MLBUILog(TEXT("Not Set MenuWidget Return VerticalBox"),true,ELogVerbosity::Error);
        return nullptr;
        break;
    case VAlign_Bottom:
        return FooterVerticalBox->AddChild(ParticalWidget);
        break;
    default: ;
    }

    return nullptr;
}

void UBaseUI::RegisterElement(UParticalWidget* Element)
{
    for (const auto* a : AllParticalWidget)
    {
        if(a && Element->Info.ID != NAME_None)
            ensureMsgf( a->Info.ID != Element->Info.ID,TEXT("Widget ID Repeat"));
    }
    AllParticalWidget.AddUnique(Element);
}


