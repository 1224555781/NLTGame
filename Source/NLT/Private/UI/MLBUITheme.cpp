// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MLBUITheme.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxString.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Slider.h"
#include "Components/Spacer.h"
#include "Core/NLTLog.h"
#include "Engine/DataTable.h"
#include "RTTI/GlobalDispatcher.h"
#include "UI/NLTButton.h"
#include "UI/NLTCheckBox.h"
#include "UI/NLTComboBoxString.h"
#include "UI/NLTEditableTextBox.h"
#include "UI/NLTSlider.h"
#include "Util/NLTUtilityFunctionLibrary.h"

#define FILLWIDTH -1

class UComboBoxString;
const FString& ContenString =TEXT("Not Find DataTable Row");
const FSlateColor& GraySlateColor =FSlateColor(FLinearColor::Gray);
UMLBUITheme::UMLBUITheme()
{
    bSetCustomButtonColor =false;
    bSetCustomButtonSound =false;
    bSetCustomCheckBoxColor = false;
    bSetCustomCheckBoxSound = false;
    bSetCustomInputTextColor = false;
    bSetCustomSliderColor =false;
    CustomForegroundColor = FSlateColor(FColor::White);
    CustomBackgroundColor = FSlateColor(FColor::White);
}

bool UMLBUITheme::SetTheme(EUITheme m_UITheme)
{
    UITheme =m_UITheme;
    TEnumAsByte<EUITheme> T= UITheme;
    const FName RowName= UEnum::GetValueAsName<EUITheme>(UITheme);
    for (auto it = AllThemeDataTable.CreateIterator();it;++it)
    {
        //
        //if (it->Get<1>() /*&& (**it->Value())*/)
        //{
            switch (it.Key())
            {
            case EUIThemeDataType::MiscData:
                MiscData = it.Value()->FindRow<FNLTThemeData>(RowName,*ContenString);
                break;
            case EUIThemeDataType::ButtonData:
                ButtonData = it.Value()->FindRow<FNLTButtonData>(RowName,*ContenString);
                break;
            case EUIThemeDataType::CheckBoxData:
                CheckBoxData = it.Value()->FindRow<FNLTCheckBoxData>(RowName,*ContenString);
                break;
            case EUIThemeDataType::ComboBoxData:
                ComboBoxData = it.Value()->FindRow<FNLTComboBoxData>(RowName,*ContenString);
                break;
            case EUIThemeDataType::SliderData:
                SliderData = it.Value()->FindRow<FNLTSliderData>(RowName,*ContenString);
                break;
            case EUIThemeDataType::TextInputData:
                TextInputData = it.Value()->FindRow<FNLTTextInputData>(RowName,*ContenString);
                break;
            default: ;
            }
       // }
        //else
        //{
           // verifyf(false,TEXT("AllThemeDataTable Map DataValue Not Set"));
       // }
    }
    
    
    return true;
}

void UMLBUITheme::SetThemeColor(const TMap<EUIColorType, FSlateColor>& m_Themecolors)
{
    ThemeColors = m_Themecolors;
    
}

void UMLBUITheme::ApplyTheme(UParticalWidget* ParticalWidget)
{
    switch (ParticalWidget->WidgetType)
    {
    case EWidgetType::Button:
        {
            
            UButton* Button = nullptr;
            UTextBlock* ButtonTextBlock = nullptr;
            ParticalWidget->Execute_GetButtonElements(ParticalWidget,Button,ButtonTextBlock);
            
            if (Button&&ButtonTextBlock)
            {
                FSlateColor ButtonSlateColor;
                FSlateFontInfo ButtonFontInfo;
                FButtonStyle ButtonStyle;
                GetButtonData(ButtonStyle,ButtonFontInfo,ButtonSlateColor,ParticalWidget->Info);
                Button->WidgetStyle = ButtonStyle;
                ButtonTextBlock->SetFont(ButtonFontInfo);
                ButtonTextBlock->SetText(ParticalWidget->Info.Caption);
                ButtonTextBlock->SetColorAndOpacity(ButtonSlateColor);
                
                UNLTButton* NLTButton = Cast<UNLTButton>(Button);
                if (NLTButton)
                {
                    
                    if (!ParticalWidget->Info.bUseDispacher)
                    {
                        if(ParticalWidget->Info.EventDelegate.IsSameType<FOnClicked>())
                            NLTButton->SetOnclickedDelegate(ParticalWidget->Info.EventDelegate.AnyCast<FOnClicked>());
                        else
                            MLBUILog(TEXT("Info->EventDelegate.AnyCast<FOnClicked>() Failed"),true,ELogVerbosity::Error);
                    }
                    else
                    {
                       
                    };
                    
                }
            }
        }
        break;
    case EWidgetType::CheckBox:
        {
            SetCheckBoxStyle();
            UNLTCheckBox* CheckBox = nullptr;
            UTextBlock* CheckBoxTextBlock = nullptr;
            ParticalWidget->Execute_GetCheckBoxElements(ParticalWidget,CheckBox,CheckBoxTextBlock);

            if (!CheckBox || !CheckBoxTextBlock)
            {
                MLBUILog(TEXT("CheckBox || CheckBoxTextBlock == NULL"));
                return;
            }
                
            CheckBox->WidgetStyle = CheckBoxStyle;
            
            CheckBoxTextBlock->SetFont(MiscData->TextElementFont);
            CheckBoxTextBlock->SetText(ParticalWidget->Info.Caption);
            CheckBoxTextBlock->ColorAndOpacity = TextBlockColor;
            SetCaptionAndWidgetWidth(ParticalWidget);
            if (!ParticalWidget->Info.bUseDispacher)
            {
                CheckBox->SetEventDelegate(ParticalWidget->Info.EventDelegate);
            }
            else
            {
                CheckBox->OnCheckStatChanged.BindLambda([ParticalWidget](ECheckBoxState NewState)
                {
                    const auto* Dispacher = UNLTUtilityFunctionLibrary::GetDispatcher(ParticalWidget);
                    Dispacher->GetDispacher()->TriggerEvent_CPP(ParticalWidget->Info.ID.ToString(),NewState);       
                });
            }
            
        }
        break;
    case EWidgetType::ComboBox:
        {
            SetComboBoxStyle(ParticalWidget);
            UNLTComboBoxString* ComboBox = nullptr;
            UTextBlock* ComboBoxTextBlock = nullptr;
            ParticalWidget->Execute_GetComboBoxElements(ParticalWidget,ComboBox,ComboBoxTextBlock);
            if(!ComboBox || !ComboBoxTextBlock)
                MLBUILog(TEXT("!ComboBox || !ComboBoxTextBlock == NULL"));
            ComboBox->WidgetStyle = ComboBoxStyle;
            ComboBoxTextBlock->Font = MiscData->TextElementFont;
            ComboBoxTextBlock->ColorAndOpacity = MiscData->TextElementColor;
            ComboBoxTextBlock->SetText(ParticalWidget->Info.Caption);
            SetCaptionAndWidgetWidth(ParticalWidget);
            if (!ParticalWidget->Info.bUseDispacher)
            {
                ComboBox->SetEventDelegate(ParticalWidget->Info.EventDelegate);
            }
            else
            {
                ComboBox->ComboBoxStatChanged.BindLambda([ParticalWidget](FString Item, ESelectInfo::Type SelectionType)
                {
                    const auto* Dispacher = UNLTUtilityFunctionLibrary::GetDispatcher(ParticalWidget);
                    TTuple<FString,ESelectInfo::Type>ComboBoxParam;
                    ComboBoxParam.Get<0>() = Item;
                    ComboBoxParam.Get<1>()= SelectionType;
                    Dispacher->GetDispacher()->TriggerEvent_CPP(ParticalWidget->Info.ID.ToString(),ComboBoxParam);       
                });
            }
        }
        break;
    case EWidgetType::Slider:
        {
            SetSliderWidgetStyle();
            UNLTSlider* Slider = nullptr;
            UTextBlock* SliderTextBlock = nullptr;
            ParticalWidget->Execute_GetSliderElements(ParticalWidget,Slider,SliderTextBlock);
            if(!Slider || !SliderTextBlock)
                MLBUILog(TEXT("!Slider || !SliderTextBlock == NULL"));
            Slider->WidgetStyle = SliderStyle;
            SliderTextBlock->Font = MiscData->TextElementFont;
            SliderTextBlock->ColorAndOpacity = MiscData->TextElementColor;
            SliderTextBlock->SetText(ParticalWidget->Info.Caption);
            SetCaptionAndWidgetWidth(ParticalWidget);
            if (!ParticalWidget->Info.bUseDispacher)
            {
                Slider->SetEventDelegate(ParticalWidget->Info.EventDelegate);
            }
            else
            {
                Slider->SliderStatChanged.BindLambda([ParticalWidget](float Value)
                {
                    const auto* Dispacher = UNLTUtilityFunctionLibrary::GetDispatcher(ParticalWidget);
                    Dispacher->GetDispacher()->TriggerEvent_CPP(ParticalWidget->Info.ID.ToString(),Value);       
                });
            }
        }
        break;
    case EWidgetType::TextInput:
        {
            SetEditableTextBoxStyle();
            UNLTEditableTextBox* EditableTextBox = nullptr;
            UTextBlock* InputTextTextBlock = nullptr;
            ParticalWidget->Execute_GetInputTextElements(ParticalWidget,EditableTextBox,InputTextTextBlock);
            if (!EditableTextBox || !InputTextTextBlock)
                MLBUILog(TEXT("!EditableTextBox || !InputTextTextBlock == NULL"));
            EditableTextBox->WidgetStyle = EditableTextStyle; 
        
            
            InputTextTextBlock->SetFont(MiscData->TextElementFont);
            InputTextTextBlock->SetColorAndOpacity(MiscData->TextElementColor);
            InputTextTextBlock->SetText(ParticalWidget->Info.Caption);
            SetCaptionAndWidgetWidth(ParticalWidget);
            if (!ParticalWidget->Info.bUseDispacher)
            {
                EditableTextBox->SetEventDelegate(ParticalWidget->Info.EventDelegate);
            }
            else
            {
                EditableTextBox->EditableTextStatChanged.BindLambda([ParticalWidget](const FText& Text, ETextCommit::Type CommitMethod)
                {
                    const auto* Dispacher = UNLTUtilityFunctionLibrary::GetDispatcher(ParticalWidget);
                    TTuple<const FText& , ETextCommit::Type>EditableTextParam{Text,CommitMethod};
                    //EditableTextParam.Value = CommitMethod;
                    Dispacher->GetDispacher()->TriggerEvent_CPP(ParticalWidget->Info.ID.ToString(),EditableTextParam);       
                });
            }
            
        }
        break;
    case EWidgetType::TextLine:
        {
            UTextBlock* TextLineTextBlock = nullptr;
            ParticalWidget->Execute_GetTextLineElements(ParticalWidget,TextLineTextBlock);
            if(!TextLineTextBlock)
                return;
            switch (ParticalWidget->Info.VerticalAlignment)
            {
                case EVerticalAlignment::VAlign_Top :
                    TextLineTextBlock->SetFont(MiscData->TextHeaderFont);
                    TextLineTextBlock->SetColorAndOpacity(MiscData->TextHeaderColor);
                    break; 
                case EVerticalAlignment::VAlign_Bottom :
                    TextLineTextBlock->SetFont(MiscData->TextFooterFont);
                    TextLineTextBlock->SetColorAndOpacity(MiscData->TextFooterColor);
                    break; 
                case EVerticalAlignment::VAlign_Center :
                    TextLineTextBlock->SetFont(MiscData->TextElementFont);
                    TextLineTextBlock->SetColorAndOpacity(MiscData->TextElementColor);
                    break; 
            default: ;
            }
            
           
        }
        break;
    case EWidgetType::Tooltip:
        {
            UImage* TooltipImage = nullptr;
            UTextBlock* TooltipTextBlock = nullptr;
            ParticalWidget->Execute_GetTooltipElements(ParticalWidget,TooltipImage,TooltipTextBlock);
            if (TooltipImage && TooltipTextBlock)
            {
                FSlateColor TooltipSlateColor;
                FSlateFontInfo TooltipFontInfo;
                auto a= GetTooltipData(TooltipFontInfo,TooltipSlateColor);
                TooltipImage->SetBrush(a);
                TooltipTextBlock->SetFont(TooltipFontInfo);
                if(!ParticalWidget->Tooltip.IsEmpty())
                    TooltipTextBlock->SetText(ParticalWidget->Tooltip);
                TooltipTextBlock->SetColorAndOpacity(TooltipSlateColor);
            }
           
        }
        break;
    case EWidgetType::Spacer: break;
    case EWidgetType::Menu: break;
    default: ;
    }
}

FSlateBrush UMLBUITheme::GetTooltipData(FSlateFontInfo& FontInfo, FSlateColor& FontColor) const
{
    //不需要再检查MiscData 由创建时保证创建成功
    FSlateBrush ret;
    ret.ImageSize = MiscData->ToolTipBackgroundSize;
    ret.DrawAs = MiscData->ToolTipBackgroundDrawAS;
    ret.Margin=MiscData->ToolTipBackgroundMargin;
    ret.SetResourceObject( MiscData->ToolTipBackgroundTexture);
    FontColor = MiscData->TextElementColor;
    FontInfo = MiscData->TextElementFont;
    return ret;
}

void UMLBUITheme::GetButtonData(FButtonStyle& ButtonStyle,FSlateFontInfo& FontInfo, FSlateColor& FontColor,const FBuildWidgetInfo& Info)
{
    CreateButtonColors();
    if (bSetCustomButtonSound)
    {
        ButtonPressSound = Info.PressSoundBase;
        ButtonReleaseSound = Info.ExtraSoundBase;
    }
   
    FSlateBrush ButtonDisableBrush = ButtonData->ToSlateBrush();
    ButtonDisableBrush.TintColor = ButtonDisableColor;
    FSlateBrush ButtonPressBrush = ButtonData->ToSlateBrush();
    ButtonPressBrush.TintColor = ButtonPressColor;
    FSlateBrush ButtonHoveredBrush = ButtonData->ToSlateBrush();
    ButtonHoveredBrush.TintColor = ButtonHoveredColor;
    FSlateBrush ButtonNormalBrush = ButtonData->ToSlateBrush();
    ButtonNormalBrush.TintColor = ButtonNormalColor;

    ButtonStyle.Disabled  = ButtonDisableBrush;
    ButtonStyle.Hovered = ButtonHoveredBrush;
    ButtonStyle.Pressed = ButtonPressBrush;
    FSlateSound PressSlateSound ;
    PressSlateSound.SetResourceObject(ButtonPressSound);
    FSlateSound HoveredSlateSound ;
    HoveredSlateSound.SetResourceObject(ButtonReleaseSound);
    ButtonStyle.Normal = ButtonNormalBrush;
    ButtonStyle.SetPressedSound(PressSlateSound);
    ButtonStyle.SetHoveredSound(HoveredSlateSound);
    FontColor = MiscData->TextElementColor;
    FontInfo = MiscData->TextElementFont;
}

void UMLBUITheme::CreateButtonColors()
{
    if (!bSetCustomButtonColor)
    {
        ButtonNormalColor = MiscData->ThemeColorNormal;
        ButtonHoveredColor = MiscData->ThemeColorHover;
        ButtonPressColor = MiscData->ThemeColorExtra;
    }
    ButtonDisableColor = GraySlateColor;
    
}

void UMLBUITheme::SetCheckBoxStyle()
{
     FSlateBrush BaseCheckBoxBrushUnchecked;
            BaseCheckBoxBrushUnchecked.SetResourceObject(CheckBoxData->UnCheckTexture);
            BaseCheckBoxBrushUnchecked.Margin = FMargin();
            BaseCheckBoxBrushUnchecked.DrawAs = CheckBoxData->DrawAsType;
            BaseCheckBoxBrushUnchecked.ImageSize = CheckBoxData->ImageSize;
            
            FSlateBrush CheckBoxBrushUncheckedNormal = BaseCheckBoxBrushUnchecked;
            FSlateBrush CheckBoxBrushUncheckedPress = BaseCheckBoxBrushUnchecked;
            FSlateBrush CheckBoxBrushUncheckedHovered = BaseCheckBoxBrushUnchecked;

            FSlateBrush BaseCheckBoxBrushChecked = BaseCheckBoxBrushUnchecked;
            BaseCheckBoxBrushChecked.SetResourceObject(CheckBoxData->CheckTexture);
         
            FSlateBrush CheckBoxBrushCheckedNormal = BaseCheckBoxBrushChecked;
            FSlateBrush CheckBoxBrushCheckedPress = BaseCheckBoxBrushChecked;
            FSlateBrush CheckBoxBrushCheckedHovered = BaseCheckBoxBrushChecked;

            FSlateBrush BaseCheckBoxBrushHovered = BaseCheckBoxBrushUnchecked;
            BaseCheckBoxBrushHovered.SetResourceObject(CheckBoxData->CheckTexture);
         
            FSlateBrush CheckBoxBrushHoveredNormal = BaseCheckBoxBrushHovered;
            FSlateBrush CheckBoxBrushHoveredPress = BaseCheckBoxBrushHovered;
            FSlateBrush CheckBoxBrushHoveredHovered = BaseCheckBoxBrushHovered;
            
            if (!bSetCustomCheckBoxColor)
            {
                CheckBoxUncheckedNormalColor = MiscData->ThemeColorNormal;
                CheckBoxUncheckedHoveredColor = MiscData->ThemeColorHover;
                CheckBoxUncheckedPressColor = MiscData->ThemeColorExtra;


                CheckBoxCheckedNormalColor = MiscData->ThemeColorNormal;
                CheckBoxCheckedHoveredColor = MiscData->ThemeColorHover;
                CheckBoxCheckedPressColor = MiscData->ThemeColorExtra;

                CheckBoxHoveredNormalColor = MiscData->ThemeColorNormal;
                CheckBoxHoveredHoveredColor = MiscData->ThemeColorHover;
                CheckBoxHoveredPressColor = MiscData->ThemeColorExtra;

                TextBlockColor = MiscData->TextElementColor;
            }
            CheckBoxBrushUncheckedNormal.TintColor = CheckBoxUncheckedNormalColor;
            CheckBoxBrushUncheckedPress.TintColor = CheckBoxUncheckedPressColor;
            CheckBoxBrushUncheckedHovered.TintColor = CheckBoxUncheckedHoveredColor;

            CheckBoxBrushCheckedNormal.TintColor = CheckBoxCheckedNormalColor;
            CheckBoxBrushCheckedPress.TintColor = CheckBoxCheckedPressColor;
            CheckBoxBrushCheckedHovered.TintColor = CheckBoxCheckedHoveredColor;

            CheckBoxBrushHoveredHovered.TintColor = CheckBoxHoveredNormalColor;
            CheckBoxBrushHoveredPress.TintColor = CheckBoxHoveredPressColor;
            CheckBoxBrushHoveredHovered.TintColor = CheckBoxHoveredHoveredColor;

           
            CheckBoxStyle.Padding = CheckBoxData->NormalPadding;
            CheckBoxStyle.CheckBoxType = ESlateCheckBoxType::CheckBox;
            CheckBoxStyle.ForegroundColor = CustomForegroundColor;
            CheckBoxStyle.BorderBackgroundColor = CustomBackgroundColor;
            CheckBoxStyle.UncheckedImage = CheckBoxBrushUncheckedNormal;
            CheckBoxStyle.UncheckedPressedImage = CheckBoxBrushUncheckedPress;
            CheckBoxStyle.UncheckedHoveredImage = CheckBoxBrushUncheckedHovered;
            CheckBoxStyle.CheckedImage = CheckBoxBrushCheckedNormal;
            CheckBoxStyle.CheckedPressedImage = CheckBoxBrushCheckedPress;
            CheckBoxStyle.CheckedHoveredImage = CheckBoxBrushCheckedHovered;
            CheckBoxStyle.UndeterminedImage = CheckBoxBrushHoveredNormal;
            CheckBoxStyle.UndeterminedPressedImage = CheckBoxBrushHoveredPress;
            CheckBoxStyle.UndeterminedHoveredImage = CheckBoxBrushHoveredHovered;
           
            FSlateSound CheckBoxPressSound_M;
            FSlateSound CheckBoxUncheckSound_M;
            FSlateSound CheckBoxHoveredSound_M;
            if(bSetCustomCheckBoxSound)
            {
                CheckBoxPressSound_M.SetResourceObject(CheckBoxPressSound);
                CheckBoxUncheckSound_M.SetResourceObject(CheckBoxUncheckedSound);
                CheckBoxHoveredSound_M.SetResourceObject(CheckBoxHoveredSound);
                CheckBoxStyle.SetCheckedSound(CheckBoxPressSound_M);
                CheckBoxStyle.SetUncheckedSound(CheckBoxUncheckSound_M);
                CheckBoxStyle.SetHoveredSound(CheckBoxHoveredSound_M);
            }
}

void UMLBUITheme::SetEditableTextBoxStyle()
{
    FSlateBrush TextInputBase;
    TextInputBase.Margin = TextInputData->Padding;
    TextInputBase.DrawAs = TextInputData->DrawAsType;
    TextInputBase.ImageSize = TextInputData->ImageSize;
    TextInputBase.SetResourceObject(TextInputData->ImageTexture);
    FSlateBrush TextInputNormal = TextInputBase;
    FSlateBrush TextInputHovered = TextInputBase;
    FSlateBrush TextInputReadOnly =TextInputBase;
    FSlateBrush TextInputFocus = TextInputBase;

    if (!bSetCustomInputTextColor)
    {
        InputTextNormalColor = MiscData->ThemeColorNormal;
        InputTextHoveredColor = MiscData->ThemeColorHover;
        InputTextFocusColor = MiscData->ThemeColorExtra;                  
    }
    InputTextReadOnlyColor = GraySlateColor;
    TextInputNormal.TintColor = InputTextNormalColor;
    TextInputHovered.TintColor = InputTextHoveredColor;
    TextInputReadOnly.TintColor = GraySlateColor;
    TextInputFocus.TintColor = InputTextFocusColor;
            
           
    EditableTextStyle.SetBackgroundImageNormal(TextInputNormal)
    .SetBackgroundImageHovered(TextInputHovered)
    .SetBackgroundImageFocused(TextInputFocus)
    .SetBackgroundImageReadOnly(TextInputReadOnly)
    .SetForegroundColor(MiscData->TextElementColor)
    .SetPadding(TextInputData->Padding)
    .SetFont(MiscData->TextElementFont)
    ;

}

void UMLBUITheme::SetComboBoxStyle(UParticalWidget* ParticalWidget)
{
   FComboButtonStyle ComboButtonStyle;
            FSlateBrush ComboBoxBase;
            ComboBoxBase.SetImageSize(ComboBoxData->ImageSize);
            ComboBoxBase.DrawAs = ComboBoxData->DrawAsType;
            // ComboBoxBase.Margin = ComboBoxData.
            ComboBoxBase.SetResourceObject(ComboBoxData->ImageTexture);
            FSlateBrush ComboBoxNormal =ComboBoxBase;
            FSlateBrush ComboBoxPress = ComboBoxBase;
            FSlateBrush ComboBoxHovered = ComboBoxBase;
            FSlateBrush ComboBoxDisable = ComboBoxBase;

            FSlateBrush ComboBoxDownArrowSlateBrush;
            FSlateBrush ComboBoxBorderBrush;
            
            if(!bSetCustomComboBoxColor)
            {
                ComboBoxNormalColor = MiscData->ThemeColorNormal;
                ComboBoxHoveredColor = MiscData->ThemeColorHover;
                ComboBoxPressColor = MiscData->ThemeColorExtra; 
            }
            ComboBoxDisable.TintColor = GraySlateColor;
            ComboBoxNormal.TintColor = ComboBoxNormalColor;
            ComboBoxHovered.TintColor = ComboBoxHoveredColor;
            ComboBoxPress.TintColor = ComboBoxPressColor;

            ComboBoxBorderBrush.TintColor = ComboBoxNormalColor;
            ComboBoxBorderBrush.DrawAs = ComboBoxData->BorderDrawAsType;
            ComboBoxBorderBrush.Margin = ComboBoxData->BorderPadding;
            ComboBoxBorderBrush.SetResourceObject(ComboBoxData->BorderTexture);
            ComboBoxBorderBrush.ImageSize = ComboBoxData->BorderSize;
            
            
            FSlateSound ComboBoxPressSound;
            ComboBoxPressSound.SetResourceObject(ParticalWidget->Info.PressSoundBase);

            FSlateSound ComboBoxSelectSound;
            ComboBoxSelectSound.SetResourceObject(ParticalWidget->Info.ExtraSoundBase);
            
            ComboBoxStyle.SetPressedSound(ComboBoxPressSound);
            ComboBoxStyle.SetSelectionChangeSound(ComboBoxSelectSound);
            FButtonStyle ComboBoxButtonStyle;
            ComboBoxButtonStyle
            .SetNormal(ComboBoxNormal)
            .SetHovered(ComboBoxHovered)
            .SetPressed(ComboBoxPress)
            .SetDisabled(ComboBoxDisable)
            .SetNormalPadding(ComboBoxData->NormalPadding)
            .SetPressedPadding(ComboBoxData->PressPadding);

            ComboBoxDownArrowSlateBrush.DrawAs = ComboBoxData->DrawAsType;
            ComboBoxDownArrowSlateBrush.ImageSize = ComboBoxData->ArrowSize;
            ComboBoxDownArrowSlateBrush.SetResourceObject(ComboBoxData->ArrowTexture);
            ComboBoxDownArrowSlateBrush.Margin = ComboBoxData->ArrowPadding;
            
            
            ComboButtonStyle.SetButtonStyle(ComboBoxButtonStyle)
            .SetDownArrowImage(ComboBoxDownArrowSlateBrush)
            .SetShadowOffset(FVector2D(0.f))
            .SetShadowColorAndOpacity(FLinearColor::Black)
            .SetMenuBorderPadding(ComboBoxData->MenuBorderPadding)
            .SetMenuBorderBrush(ComboBoxBorderBrush);
           
            ComboBoxStyle.SetComboButtonStyle(ComboButtonStyle);

  
}
void UMLBUITheme::SetSliderWidgetStyle()
{
	   FSlateBrush SliderBarBase;
            SliderBarBase.DrawAs  =SliderData->BarDrawAsType;
            SliderBarBase.Margin  =FMargin();
            SliderBarBase.ImageSize = SliderData->BarImageSize;
            SliderBarBase.SetResourceObject(SliderData->BarImage);

            FSlateBrush SliderThumbBase;
            SliderThumbBase.DrawAs  =SliderData->ThumbDrawAsType;
            SliderThumbBase.Margin  =FMargin();
            SliderThumbBase.ImageSize = SliderData->ThumbImageSize;
            SliderThumbBase.SetResourceObject(SliderData->ThumbImage);

            FSlateBrush SliderNormalBarImage = SliderBarBase;
            FSlateBrush SliderNormalThumbImage= SliderThumbBase;
            FSlateBrush SliderHoveredBarImage= SliderBarBase;
            FSlateBrush SliderHoveredThumbImage = SliderThumbBase;;
            FSlateBrush SliderDisableBarImage = SliderBarBase;
            FSlateBrush SliderDisableThumbImage = SliderThumbBase;;
            
            if(!bSetCustomSliderColor)
            {
                SliderNormalBarImageColor = SliderData->BarNormalTint;
                SliderNormalThumbImageColor = SliderData->ThumbNormalTint;
                SliderDisableThumbImageColor = SliderData->ThumbDisabledTint;
                SliderDisableBarImageColor = SliderData->BarDisabledTint;
                
            }
            SliderNormalBarImage.TintColor = SliderNormalBarImageColor;
            SliderNormalThumbImage.TintColor = SliderNormalThumbImageColor;
            SliderHoveredBarImage.TintColor = SliderNormalBarImageColor;
            SliderHoveredThumbImage.TintColor = SliderNormalThumbImageColor;
            SliderDisableBarImage.TintColor = SliderDisableBarImageColor;
            SliderDisableThumbImage.TintColor = SliderDisableThumbImageColor;
            
           
            
            SliderStyle.SetNormalBarImage(SliderNormalBarImage)
            .SetNormalThumbImage(SliderNormalThumbImage)
            //.SetHoveredBarImage(SliderHoveredBarImage)
            //.SetNormalThumbImage(SliderHoveredThumbImage)
            .SetDisabledBarImage(SliderDisableBarImage)
            .SetDisabledThumbImage(SliderDisableThumbImage)
            .SetBarThickness(2.f);

}

void UMLBUITheme::SetCaptionAndWidgetWidth(UParticalWidget* Widget) const
{
    float Width = Widget->Info.Width;
    USpacer* Spacer =Cast<USpacer>(Widget->WidgetTree->FindWidget(FName(TEXT("Spacer"))));
    if (Spacer)
    {
        UHorizontalBoxSlot* Slot =  Cast<UHorizontalBoxSlot>(Spacer->Slot);
        if (!Slot)
            return;
        if (Width == FILLWIDTH)
        {
            Slot->SetSize(FSlateChildSize());
        }
        else
        {
            FSlateChildSize Size;
            Size.SizeRule = ESlateSizeRule::Automatic;
            Slot->SetSize(Size);
            Slot->SetPadding(FMargin( Width,0,0,0));
            
        }
    }
    else
    {
        MLBUILog(TEXT("Check Your Widget Spacer Name Is Spacer?"),false,ELogVerbosity::Error);        
    }
}
