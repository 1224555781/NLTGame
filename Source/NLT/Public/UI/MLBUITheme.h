// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "ParticalWidget.h"
#include "ThemeData.h"
#include "Brushes/SlateColorBrush.h"
#include "Core/NLTDataTypes.h"
#include "UObject/NoExportTypes.h"
#include "MLBUITheme.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NLT_API UMLBUITheme : public UObject
{
	GENERATED_BODY()
	UMLBUITheme();
public:
	
	bool SetTheme(EUITheme m_UITheme);
	void SetThemeColor(const TMap<EUIColorType, FSlateColor>& m_Themecolors);

	//UFUNCTION(BlueprintCallable,Category=UITheme)
	void ApplyTheme(UParticalWidget* ParticalWidget);

	UPROPERTY(EditDefaultsOnly,Category = UITheme)
	TMap<TEnumAsByte< EUIThemeDataType>,UDataTable*>AllThemeDataTable;

	////////////////////////////
	///返回各个样式数据
	///
	FSlateBrush GetTooltipData(FSlateFontInfo& FontInfo,FSlateColor& FontColor) const;
	void GetButtonData(FButtonStyle& ButtonStyle,FSlateFontInfo& FontInfo,FSlateColor& FontColor,const FBuildWidgetInfo& Info);


	////////////////////
	///Button Data
	///
	UPROPERTY(EditDefaultsOnly,Category = ButtonData)
	bool bSetCustomButtonColor;
	//如果不选择则使用默认音效
	UPROPERTY(EditDefaultsOnly,Category = ButtonData)
	bool bSetCustomButtonSound;
	
	UPROPERTY(EditDefaultsOnly,Category = ButtonData)
	FSlateColor ButtonNormalColor;
	UPROPERTY(EditDefaultsOnly,Category = ButtonData)
	FSlateColor ButtonHoveredColor;
	UPROPERTY(EditDefaultsOnly,Category = ButtonData)
	FSlateColor ButtonPressColor;
	
	UPROPERTY(EditDefaultsOnly,Category = ButtonData)
	USoundBase* ButtonPressSound;
	UPROPERTY(EditDefaultsOnly,Category = ButtonData)
	USoundBase* ButtonReleaseSound;
	//设置成灰色不变
	UPROPERTY(EditDefaultsOnly,Category = ButtonData)
	FSlateColor ButtonDisableColor;
	UFUNCTION(BlueprintCallable,Category =ButtonData)
	void CreateButtonColors();
	//////////////////////////
	///End
	/////////////////////////
	///
	////////////////////
	///CheckBox Data
	///
	///
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	bool bSetCustomCheckBoxColor;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	bool bSetCustomCheckBoxSound;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CheckBoxUncheckedNormalColor;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CheckBoxUncheckedPressColor;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CheckBoxUncheckedHoveredColor;

	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CheckBoxCheckedNormalColor;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CheckBoxCheckedPressColor;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CheckBoxCheckedHoveredColor;

	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CheckBoxHoveredNormalColor;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CheckBoxHoveredPressColor;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CheckBoxHoveredHoveredColor;

	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CustomForegroundColor;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor CustomBackgroundColor;

	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	FSlateColor TextBlockColor;


	
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	USoundBase* CheckBoxPressSound;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	USoundBase* CheckBoxUncheckedSound;
	UPROPERTY(EditDefaultsOnly,Category = CheckBoxData)
	USoundBase* CheckBoxHoveredSound;

	FCheckBoxStyle CheckBoxStyle;

	void SetCheckBoxStyle();
	//////////////////////////////////
	///End
	//////////////////////////////////
	///
	////////////////////
	///InputText Data
	///
	UPROPERTY(EditDefaultsOnly,Category = InputTextData)
	bool bSetCustomInputTextColor;

	UPROPERTY(EditDefaultsOnly,Category = InputTextData)
	FSlateColor InputTextNormalColor;
	UPROPERTY(EditDefaultsOnly,Category = InputTextData)
	FSlateColor InputTextFocusColor;
	UPROPERTY(EditDefaultsOnly,Category = InputTextData)
	FSlateColor InputTextReadOnlyColor;
	UPROPERTY(EditDefaultsOnly,Category = InputTextData)
	FSlateColor InputTextHoveredColor;

	FEditableTextBoxStyle EditableTextStyle;

	void SetEditableTextBoxStyle();
	//////////////////////////////////
	///End
	//////////////////////////////////
	///
	////////////////////
	///ComboBox Data
	///
	UPROPERTY(EditDefaultsOnly,Category = InputTextData)
	bool bSetCustomComboBoxColor;

	UPROPERTY(EditDefaultsOnly,Category = InputTextData)
	FSlateColor ComboBoxNormalColor;
	UPROPERTY(EditDefaultsOnly,Category = InputTextData)
	FSlateColor ComboBoxPressColor;
	UPROPERTY(EditDefaultsOnly,Category = InputTextData)
	FSlateColor ComboBoxHoveredColor;

	ETextJustify::Type ComboTextJustify;

	FComboBoxStyle ComboBoxStyle;

	void SetComboBoxStyle(UParticalWidget* ParticalWidget);
	////////////////////////////////////
	///End
	////////////////////////////////////
	///Slider Data
	////////////////////////////////////
	///
	UPROPERTY(EditDefaultsOnly,Category = SliderData)
	bool bSetCustomSliderColor;
	
	FSlateColor SliderNormalBarImageColor;
	FSlateColor SliderNormalThumbImageColor;
	FSlateColor SliderHoveredBarImageColor;
	FSlateColor SliderHoveredThumbImageColor;
	FSlateColor SliderDisableBarImageColor;
	FSlateColor SliderDisableThumbImageColor;

	FSliderStyle SliderStyle;

	void SetSliderWidgetStyle();
	///////////////////////////
	///End
	////////////////////////
	///
	///Misc
	///
	UFUNCTION(BlueprintPure,Category = "UITheme | Misc")
	FSlateFontInfo GetTextElementsFontInfo()const{return MiscData->TextElementFont;}
	UFUNCTION(BlueprintPure,Category = "UITheme | Misc")
	FSlateColor GetTextElementsSlateColor()const {return MiscData->TextElementColor;}
	UFUNCTION(BlueprintPure,Category = "UITheme | Misc")
	FSlateColor GetComboBoxItemBG()const{return ComboBoxData->ItemBackgroundColor;}
	UFUNCTION(BlueprintPure,Category = "UITheme | Misc")
	ETextJustify::Type GetComboTextJustify()const {return ComboTextJustify;}
	
private:
	TMap<EUIColorType,FSlateColor>ThemeColors;
	EUITheme UITheme;

	FNLTThemeData* MiscData;
	FNLTButtonData* ButtonData;
	FNLTCheckBoxData* CheckBoxData;
	FNLTComboBoxData* ComboBoxData;
	FNLTSliderData* SliderData;
	FNLTTextInputData* TextInputData;


	void SetCaptionAndWidgetWidth(UParticalWidget* Widget) const;
};


