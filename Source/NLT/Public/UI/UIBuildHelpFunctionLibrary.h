// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseUI.h"
#include "Components/Button.h"
#include "Core/NLTUICore.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIBuildHelpFunctionLibrary.generated.h"

class UParticalWidget;
/**
 * 
 */
UCLASS()
class NLT_API UUIBuildHelpFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable, meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext="WorldContextObject"))
	static UBaseUI* AddButton(UObject* WorldContextObject,UBaseUI* Menu,UParticalWidget* &Button, FBuildWidgetInfo Info,float LineHeight);

	//UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable, meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext="WorldContextObject"))
    static UBaseUI* AddRowButtons(UObject* WorldContextObject,UBaseUI* Menu,TArray<FBuildWidgetInfo> Infos,const FBuildWidgetInfo& WidgetInfo,float LineHeight,float Spacer,TArray<UParticalWidget*>&Buttons);

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable, meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext="WorldContextObject"))
	static UBaseUI* AddCheckBox(UObject* WorldContextObject,UBaseUI* Menu,UParticalWidget* &CheckBox,const FBuildWidgetInfo& Info,float LineHeight ,bool bInitChecked = false);

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable, meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext="WorldContextObject"))
    static UBaseUI* AddEditableTextBox(UObject* WorldContextObject,UBaseUI* Menu,UParticalWidget* &EditableTextBox,const FBuildWidgetInfo& Info,float LineHeight ,FText HintText);
	
	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable,meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext = "WorldContextObject"))
    static UBaseUI* AddSpacer(UObject* WorldContextObject,UBaseUI* Menu,EVerticalAlignment VerticalAlignment);	

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable, meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext="WorldContextObject"))
    static UBaseUI* AddComboBox(UObject* WorldContextObject,UBaseUI* Menu,UParticalWidget* &ComboBox,FBuildWidgetInfo Info,float LineHeight ,const TArray< FString>&Options,const FString& DefaultOption,ETextJustify::Type Justify);

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable, meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext="WorldContextObject"))
    static UBaseUI* AddTextLine(UObject* WorldContextObject,UBaseUI* Menu,UParticalWidget* &TextLine,FBuildWidgetInfo Info,float LineHeight ,FText Text);

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable, meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext="WorldContextObject"))
    static UBaseUI* AddSlider(UObject* WorldContextObject,UBaseUI* Menu,UParticalWidget* &Slider,FBuildWidgetInfo Info,float LineHeight ,float DefaultValue=0.f);

	//确定当前添加内容的区块
	// ---- 无需选择
	// --|-- 0在左 ，1在右
	// -|-|- 0   1   2 
	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable, meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext="WorldContextObject"))
	static UBaseUI* SelectColumn(UObject* WorldContextObject,UBaseUI* Menu,uint8 Column);

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintPure,meta=(WorldContext="WorldContextObject"))
	static UNLTUICore* GetUICore(const UObject* WorldContextObject);

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable,meta = (WorldContext = "WorldContextObject"))
	static void ShowUI(const UObject* WorldContextObject,UUserWidget* ShowWidget = nullptr);
    
	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable,meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext = "WorldContextObject"))
    static UBaseUI* SetTooltip(UObject* WorldContextObject,UBaseUI* Menu,UParticalWidget* TipWidget,const FText& Tip);

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable,meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext = "WorldContextObject"))
	static UPanelSlot* AddElementToMenu(UObject* WorldContextObject,UBaseUI* Menu,UParticalWidget* AddWidget);

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable,meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext = "WorldContextObject"))
	static void CheckAutoSpacer(UObject* WorldContextObject,UBaseUI* Menu);

	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable, meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext = "WorldContextObject"))
	static bool SetPaddingAndHorizontalAlignment(UObject* WorldContextObject,UVerticalBoxSlot* VSlot,UHorizontalBoxSlot* Left,UHorizontalBoxSlot* Right,FMargin Padding,EHorizontalAlignment HorizontalAlignment);
	
	UFUNCTION(Category=UIBuildHelpFunctionLibrary,BlueprintCallable,meta = (HidePin = "WorldContextObject",DefaultToSelf,WorldContext = "WorldContextObject"))
	static void SetHorizontalSize(UObject* WorldContextObject,UHorizontalBoxSlot* Slot,float Value,ESlateSizeRule::Type Rule);
};
