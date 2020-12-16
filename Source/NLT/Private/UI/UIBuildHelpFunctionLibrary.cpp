// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIBuildHelpFunctionLibrary.h"



#include "Blueprint/WidgetTree.h"
#include "Components/ComboBoxString.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Core/NLTGameInstance.h"
#include "Core/NLTLog.h"
#include "Kismet/GameplayStatics.h"
#include "UI/NLTCheckBox.h"
#include "UI/NLTComboBoxString.h"
#include "UI/NLTEditableTextBox.h"
#include "UI/NLTSlider.h"
#include "UI/ParticalWidget.h"

UBaseUI* UUIBuildHelpFunctionLibrary::AddButton(UObject* ContexObject, UBaseUI* Menu,
    UParticalWidget*  &Button, FBuildWidgetInfo BuildInfo, float LineHeight)
{
    const auto* m_class = GetUICore(ContexObject)->ChildWidgets.Find(EWidgetType::Button);
    //有可能指针悬空
    if(!m_class || ! *m_class)
        return nullptr;
    Button = CreateWidget<UParticalWidget>(Menu,*m_class);
    Button->Info = BuildInfo;
    Button->OwnerUI = Menu;
    if(LineHeight > 0.f)
        Button->LineHeight = LineHeight;
    SetTooltip(ContexObject,Menu,Button,BuildInfo.Tooltip);
    auto a =AddElementToMenu(ContexObject,Menu,Button);
    UVerticalBoxSlot* VSlot = Cast<UVerticalBoxSlot>(a);
    UHorizontalBoxSlot* Left = nullptr;
    UHorizontalBoxSlot* Right = nullptr;
    Button->Execute_GetButtonSlots(Button,Left,Right);
    if (!Left || !Right)
    {
        MLBUILog(TEXT("Not Set Button Slot Need Return From BP"),true,ELogVerbosity::Error);
        return Menu;
    }

    SetPaddingAndHorizontalAlignment(ContexObject,VSlot,Left,Right,BuildInfo.Padding,BuildInfo.HorizontalAlignment);
    GetUICore(ContexObject)->GetUITheme(Menu->Info.UIType)->ApplyTheme(Button);
    
    return Menu;
}

UBaseUI* UUIBuildHelpFunctionLibrary::AddRowButtons(UObject* WorldContextObject, UBaseUI* Menu,
     TArray<FBuildWidgetInfo>Infos,const FBuildWidgetInfo& WidgetInfo, float LineHeight, float Spacer, TArray<UParticalWidget*>& Buttons)
{
    const auto* m_class = GetUICore(WorldContextObject)->ChildWidgets.Find(EWidgetType::Row);
    //有可能指针悬空
    if(!m_class || ! *m_class)
        return nullptr;
    auto* RowButton =CreateWidget<UParticalWidget>(Menu,*m_class);
    RowButton->Info = WidgetInfo;
    RowButton->OwnerUI = Menu;
    auto content_w = RowButton->WidgetTree->FindWidget(TEXT("Content"));
    auto content = Cast<UHorizontalBox>(content_w);
    if(!content)
    {
        MLBUILog(TEXT("auto content = Cast<UHorizontalBox>(content_w); FALSE"));
        return Menu;
    }
    auto* RowButtonsSlot =AddElementToMenu(WorldContextObject,Menu,RowButton);
    
    for (int8 m_index = 0;m_index < Infos.Num(); ++m_index)
    {
        
        const auto* m_b_class = GetUICore(WorldContextObject)->ChildWidgets.Find(EWidgetType::Button);
        //有可能指针悬空
        if(!m_b_class || ! *m_b_class)
            return nullptr;
        auto* Button = CreateWidget<UParticalWidget>(RowButton,*m_b_class);
        Button->Info = Infos[m_index];
        Button->OwnerUI = Menu;
        if(LineHeight > 0.f)
            Button->LineHeight = LineHeight;
        SetTooltip(WorldContextObject,Menu,Button,Infos[m_index].Tooltip);
        UHorizontalBoxSlot* ButtonSlot = Cast<UHorizontalBoxSlot>(Button->Slot);
        if (Infos[m_index].HorizontalAlignment == EVerticalAlignment::VAlign_Fill && ButtonSlot)
        {
            ButtonSlot->SetSize(FSlateChildSize());
            if (Spacer>0 && m_index< Infos.Num())
            {
                ButtonSlot->SetPadding(FMargin(0,0,Spacer,0));
            }
        }
        
        GetUICore(WorldContextObject)->GetUITheme(Menu->Info.UIType)->ApplyTheme(Button);
        content->AddChild(Button);
    }
    
    auto* content_Left =Cast<UHorizontalBoxSlot>( RowButton->WidgetTree->FindWidget(TEXT("Left")));
    auto* content_Right =Cast<UHorizontalBoxSlot>( RowButton->WidgetTree->FindWidget(TEXT("Right")));
    auto* conten_Slot = Cast<UHorizontalBoxSlot>(content->Slot);

    if (content_Left!=nullptr && content_Left!=nullptr)
    {
        auto a = FSlateChildSize(ESlateSizeRule::Automatic);
        a.Value = 0;
        if (WidgetInfo.HorizontalAlignment ==EHorizontalAlignment::HAlign_Fill)
        {
            conten_Slot->SetSize(FSlateChildSize());
            content_Left->SetSize(a);
            content_Right->SetSize(a);
        }
        else if (WidgetInfo.HorizontalAlignment ==EHorizontalAlignment::HAlign_Left)
        {
            content_Left->SetSize(a);
        }
        else if (WidgetInfo.HorizontalAlignment ==EHorizontalAlignment::HAlign_Right)
        {
            content_Right->SetSize(a);
        }
            
    }
    UVerticalBoxSlot* VSlot = Cast<UVerticalBoxSlot>(RowButtonsSlot);
    VSlot->SetPadding(WidgetInfo.Padding);
    return Menu;
}

UBaseUI* UUIBuildHelpFunctionLibrary::AddCheckBox(UObject* ContexObject, UBaseUI* Menu,
                                                  UParticalWidget*& CheckBox,const FBuildWidgetInfo& Info, float LineHeight,bool bInitChecked)
{
    const auto* CheckBoxClass = GetUICore(ContexObject)->ChildWidgets.Find(EWidgetType::CheckBox);
    if (!CheckBoxClass || ! *CheckBoxClass)
        return nullptr;
    CheckBox = CreateWidget<UParticalWidget>(Menu,*CheckBoxClass);
    CheckBox->Info = Info;
    CheckBox->OwnerUI = Menu;
    SetTooltip(ContexObject,Menu,CheckBox,Info.Tooltip);

    UNLTCheckBox* CheckBox_m = nullptr;
    UTextBlock* CheckBoxTextBlock = nullptr;
    CheckBox->Execute_GetCheckBoxElements(CheckBox,CheckBox_m,CheckBoxTextBlock);
    verify(CheckBox_m);
   
   
    auto a = AddElementToMenu(ContexObject,Menu,CheckBox);
    
        
    UVerticalBoxSlot* VSlot = Cast<UVerticalBoxSlot>(a);
    VSlot->SetPadding(Info.Padding);
    GetUICore(ContexObject)->GetUITheme(Menu->Info.UIType)->ApplyTheme(CheckBox);
    
    if (CheckBox_m)
    {
        CheckBox_m->SetCheckedState(bInitChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
    }
    return Menu;
}

UBaseUI* UUIBuildHelpFunctionLibrary::AddEditableTextBox(UObject* ContexObject, UBaseUI* Menu,
    UParticalWidget*& EditableTextBox,const FBuildWidgetInfo& Info, float LineHeight, FText HintText)
{
    const auto* m_class = GetUICore(ContexObject)->ChildWidgets.Find(EWidgetType::TextInput);
    //有可能指针悬空
    if(!m_class || ! *m_class)
        return nullptr;
    EditableTextBox = CreateWidget<UParticalWidget>(Menu,*m_class);
    EditableTextBox->OwnerUI = Menu;
    verify(EditableTextBox);
    EditableTextBox->Info = Info;
    UNLTEditableTextBox* EditableTextBox_m = nullptr;
    UTextBlock* EditableTextBlock = nullptr;
    EditableTextBox->Execute_GetInputTextElements(EditableTextBox,EditableTextBox_m,EditableTextBlock);
   
    auto a = AddElementToMenu(ContexObject,Menu,EditableTextBox);
    UVerticalBoxSlot* VSlot = Cast<UVerticalBoxSlot>(a);
    VSlot->SetPadding(Info.Padding);
    GetUICore(ContexObject)->GetUITheme(Menu->Info.UIType)->ApplyTheme(EditableTextBox);
    if(EditableTextBox_m)
        EditableTextBox_m->SetHintText(HintText);
    return  Menu;
}

UBaseUI* UUIBuildHelpFunctionLibrary::AddSpacer(UObject* WorldContextObject, UBaseUI* Menu,
                                                EVerticalAlignment VerticalAlignment)
{
    const auto* m_class = GetUICore(WorldContextObject)->ChildWidgets.Find(EWidgetType::Spacer);
    //有可能指针悬空
    if(!m_class || ! *m_class)
        return nullptr;
    auto a= Menu->AddElement(CreateWidget<UParticalWidget>(Menu,*m_class),VerticalAlignment);
    UVerticalBoxSlot* VSlot = Cast<UVerticalBoxSlot>(a);
    VSlot->SetSize(FSlateChildSize());
    return Menu;
}

UBaseUI* UUIBuildHelpFunctionLibrary::AddComboBox(UObject* WorldContextObject, UBaseUI* Menu,
    UParticalWidget*& ComboBox, FBuildWidgetInfo Info, float LineHeight, const TArray< FString>& Options,
    const FString& DefaultOption, ETextJustify::Type Justify)
{
    const auto* m_class = GetUICore(WorldContextObject)->ChildWidgets.Find(EWidgetType::ComboBox);
    //有可能指针悬空
    if(!m_class || ! *m_class)
        return nullptr;
    ComboBox = CreateWidget<UParticalWidget>(Menu,*m_class);
    ComboBox->OwnerUI = Menu;
    verify(ComboBox);
    ComboBox->Info = Info;
    SetTooltip(WorldContextObject,Menu,ComboBox,Info.Tooltip);
    
    
    
    UNLTComboBoxString* ComboBoxString = nullptr;
    UTextBlock* ComboBoxTextBlock = nullptr;
    ComboBox->Execute_GetComboBoxElements(ComboBox,ComboBoxString,ComboBoxTextBlock);
    if(!ComboBox || !ComboBoxTextBlock)
    {
        MLBUILog(TEXT("!ComboBox || !ComboBoxTextBlock == NULL"));
        return Menu;
    }
    
   
   

    auto a = AddElementToMenu(WorldContextObject,Menu,ComboBox);
    UVerticalBoxSlot* VSlot = Cast<UVerticalBoxSlot>(a);
    VSlot->SetPadding(Info.Padding);
    GetUICore(WorldContextObject)->GetUITheme(Menu->Info.UIType)->ApplyTheme(ComboBox);

    ////////通过UItheme 给到蓝图绑定到 ComboBox 的generateitem 函数
    GetUICore(WorldContextObject)->GetUITheme(Menu->Info.UIType)->ComboTextJustify = Justify;
    for (const FString& a_option :Options)
    {
        ComboBoxString->AddOption(a_option);
        
        if(DefaultOption!= NoneString && DefaultOption == a_option)
            ComboBoxString->SetSelectedOption(DefaultOption);
    }
    if(DefaultOption == NoneString && Options.Num() >0)
        ComboBoxString->SetSelectedIndex(0);
    
    return Menu;
}

UBaseUI* UUIBuildHelpFunctionLibrary::AddTextLine(UObject* WorldContextObject, UBaseUI* Menu,
    UParticalWidget*& TextLine, FBuildWidgetInfo Info, float LineHeight, FText Text)
{
    const auto* m_class = GetUICore(WorldContextObject)->ChildWidgets.Find(EWidgetType::TextLine);
    //有可能指针悬空
    if(!m_class || ! *m_class)
        return nullptr;
    TextLine = CreateWidget<UParticalWidget>(Menu,*m_class);
   
    verify(TextLine);
    TextLine->Info = Info;
    TextLine->OwnerUI = Menu;
    UTextBlock* UText = nullptr;
    TextLine->Execute_GetTextLineElements(TextLine,UText);
    if (!UText)
    {
        MLBUILog(TEXT("Add TextLine  UTextBlock* UText = nullptr;"));
        return Menu;
    }
    
    auto a = AddElementToMenu(WorldContextObject,Menu,TextLine);
    UVerticalBoxSlot* VSlot = Cast<UVerticalBoxSlot>(a);
    UText->SetText(Text);
    GetUICore(WorldContextObject)->GetUITheme(Menu->Info.UIType)->ApplyTheme(TextLine);
    
    UHorizontalBoxSlot* Left = nullptr;
    UHorizontalBoxSlot* Right = nullptr;
    TextLine->Execute_GetTextLineSlots(TextLine,Left,Right);
    if (!Left || !Right)
    {
        MLBUILog(TEXT("Not Set TextLine Slot Need Return From BP"),true,ELogVerbosity::Error);
        return Menu;
    }
    
    SetPaddingAndHorizontalAlignment(WorldContextObject,VSlot,Left,Right,Info.Padding,Info.HorizontalAlignment);
    
    return Menu;
}

UBaseUI* UUIBuildHelpFunctionLibrary::AddSlider(UObject* WorldContextObject, UBaseUI* Menu,
    UParticalWidget*& Slider, FBuildWidgetInfo Info, float LineHeight, float DefaultValue)
{

    const auto* m_class = GetUICore(WorldContextObject)->ChildWidgets.Find(EWidgetType::Slider);
    //有可能指针悬空
    if(!m_class || ! *m_class)
        return nullptr;
    Slider= CreateWidget<UParticalWidget>(Menu,*m_class);
    verify(Slider);
    Slider->Info = Info;
    Slider->OwnerUI = Menu;
    UNLTSlider* m_Slider = nullptr;
    UTextBlock* SliderText = nullptr;
    Slider->Execute_GetSliderElements(Slider,m_Slider,SliderText);
    if(!m_Slider)
    {
        MLBUILog(TEXT("Add Slider : m_Slider == NULL"));
        return Menu;
    }
    m_Slider->SetValue(DefaultValue);
    auto a = AddElementToMenu(WorldContextObject,Menu,Slider);
    UVerticalBoxSlot* VSlot = Cast<UVerticalBoxSlot>(a);
    VSlot->SetPadding(Info.Padding);
    GetUICore(WorldContextObject)->GetUITheme(Menu->Info.UIType)->ApplyTheme(Slider);

    return Menu;
    
}

UBaseUI* UUIBuildHelpFunctionLibrary::SelectColumn(UObject* WorldContextObject, UBaseUI* Menu, uint8 Column)
{
    Menu->SetMenuWidgetIndex(Column);
    return Menu;
}

UNLTUICore* UUIBuildHelpFunctionLibrary::GetUICore(const UObject* WorldContextObject)
{
    if(!WorldContextObject)
        return  nullptr;
    UNLTGameInstance* GameInstance = Cast<UNLTGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
    return GameInstance?GameInstance->GetUICore():nullptr;
}

void UUIBuildHelpFunctionLibrary::ShowUI(const UObject* WorldContextObject,UUserWidget* ShowWidget)
{
    GetUICore(WorldContextObject)->ShowUI();
}

UBaseUI* UUIBuildHelpFunctionLibrary::SetTooltip(UObject* WorldContextObject,  UBaseUI* Menu,UParticalWidget* TipWidget, const FText& Tip)
{
    if (Tip.IsEmpty() || !Menu || !TipWidget)
        return NULL;
    
    auto tooltipclass =  Menu->UICore->ChildWidgets.Find(EWidgetType::Tooltip);
    UParticalWidget* tooltipwidget;
    if(tooltipclass && *tooltipclass)    
        tooltipwidget = CreateWidget<UParticalWidget>(TipWidget,*tooltipclass);
    else
        tooltipwidget =CreateWidget<UParticalWidget>(TipWidget);
    tooltipwidget->Tooltip = Tip;
    tooltipwidget->WidgetType = EWidgetType::Tooltip; 
    
    GetUICore(WorldContextObject)->GetUITheme(Menu->Info.UIType)->ApplyTheme(tooltipwidget);
    TipWidget->SetToolTip(tooltipwidget);
    return Menu;
}

UPanelSlot* UUIBuildHelpFunctionLibrary::AddElementToMenu(UObject* WorldContextObject, UBaseUI* Menu,
    UParticalWidget* AddWidget)
{
    if (AddWidget->Info.VerticalAlignment == EVerticalAlignment::VAlign_Center)
        CheckAutoSpacer(WorldContextObject,Menu);
    return Menu->AddElement(AddWidget,AddWidget->Info.VerticalAlignment);
}

void UUIBuildHelpFunctionLibrary::CheckAutoSpacer(UObject* WorldContextObject, UBaseUI* Menu)
{
    if (Menu->Info.bAutoSpacing)
    {
        switch (Menu->Info.UIColumn)
        {
        case Column_One: break;
        case Column_Two: 
        case Column_Three: 
        case Column_Four: 
        case Column_Five:
            AddSpacer(WorldContextObject,Menu,EVerticalAlignment::VAlign_Center);
            break;
        default: ;
        }    
    }
}

bool UUIBuildHelpFunctionLibrary::SetPaddingAndHorizontalAlignment(UObject* WorldContextObject, UVerticalBoxSlot* VSlot,
    UHorizontalBoxSlot* Left, UHorizontalBoxSlot* Right, FMargin Padding, EHorizontalAlignment HorizontalAlignment)
{
    if (!VSlot || !Left || !Right)
        return false;
    
    VSlot->SetPadding(Padding);
    switch (HorizontalAlignment)
    {
    case HAlign_Fill:
        SetHorizontalSize(WorldContextObject,Left,0,ESlateSizeRule::Automatic);
        SetHorizontalSize(WorldContextObject,Right,0,ESlateSizeRule::Automatic);
        break;
    case HAlign_Left:
        SetHorizontalSize(WorldContextObject,Left,0,ESlateSizeRule::Automatic);
        SetHorizontalSize(WorldContextObject,Right,1,ESlateSizeRule::Fill);
        break;
    case HAlign_Center:
        SetHorizontalSize(WorldContextObject,Left,1,ESlateSizeRule::Fill);
        SetHorizontalSize(WorldContextObject,Right,1,ESlateSizeRule::Fill);
        break;
    case HAlign_Right:
        SetHorizontalSize(WorldContextObject,Left,1,ESlateSizeRule::Fill);
        SetHorizontalSize(WorldContextObject,Right,0,ESlateSizeRule::Automatic);
        break;
    }
    return true;
}

void UUIBuildHelpFunctionLibrary::SetHorizontalSize(UObject* WorldContextObject, UHorizontalBoxSlot* Slot, float Value,
    ESlateSizeRule::Type Rule)
{
    FSlateChildSize Size;
    Size.Value = Value;
    Size.SizeRule = Rule;
    Slot->SetSize(Size);
}
