// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NLTUIInterface.h"
#include "Blueprint/UserWidget.h"
#include "Core/NLTDataTypes.h"



#include "ParticalWidget.generated.h"

class UNLTUICore;
class UBaseUI;
UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	Button		,
	CheckBox	,
	ComboBox	,
	Slider		,
	TextInput	,
	TextLine	,
	Tooltip		,
	Spacer		,
	Menu		,
	Row
	
};


/**
 * 
 */
UCLASS()
class NLT_API UParticalWidget : public UUserWidget ,public INLTUIInterface
{
	GENERATED_BODY()
	

	virtual void NativePreConstruct() override;
public:
	UParticalWidget(const FObjectInitializer& ObjectInitializer);

	
	UPROPERTY(BlueprintReadOnly,Category = UICore)
	UNLTUICore* Manager;
	UPROPERTY(BlueprintReadOnly,Category = UICore)
	class UBaseUI* OwnerUI;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=ParticalWidget)
	EWidgetType WidgetType;

	UPROPERTY(BlueprintReadOnly,Category = UICore)
	FBuildWidgetInfo Info;
	
	FName ID;
	FText Caption;
	FText Tooltip;
	
	//不使用的话默认值设置为 -1
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = ParticalUI)
	float LineHeight;


	//************************
	//Begin UIInterface
	void GetTooltipElements(UImage* &Image,UTextBlock* &Text)  {};

	//End UIInterface
	//////////////////////////
};
