// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "Components/CheckBox.h"
#include "Components/ComboBox.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "UObject/Interface.h"
#include "NLTUIInterface.generated.h"

class UComboBoxString;
class UButton;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNLTUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NLT_API INLTUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/////////////////////
	///
	///返回各个Widget 所需要设置的小部件 实现在蓝图类中
	///
	//////////////////////////////
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
	void GetTooltipElements(UImage* &Image,UTextBlock* &Text);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
	void GetMenuVerticalWidget(UVerticalBox* &VerticalBox);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
	void GetButtonSlots(UHorizontalBoxSlot* &Left,UHorizontalBoxSlot* &Right);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
    void GetButtonElements(UButton* &Button,UTextBlock* &Text);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
    void GetCheckBoxElements(class UNLTCheckBox* &CheckBox,UTextBlock* &Text);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
    void GetInputTextElements(class UNLTEditableTextBox* &EditableTextBox,UTextBlock* &Text);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
    void GetComboBoxElements(class UNLTComboBoxString* &ComboBox,UTextBlock* &ComboBoxText);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
    void GetTextLineElements(UTextBlock* &TextLine);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
    void GetSliderElements(class UNLTSlider* &Slider,UTextBlock* &SliderTextBlock);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = UIInterface)
    void GetTextLineSlots(UHorizontalBoxSlot* &Left,UHorizontalBoxSlot* &Right);
};
