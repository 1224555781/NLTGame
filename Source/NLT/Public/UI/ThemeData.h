// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "UObject/ObjectMacros.h"
#include "ThemeData.generated.h"

USTRUCT(BlueprintType)
struct FNLTThemeData :public FTableRowBase
{
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere)
	FSlateColor ThemeColorNormal;
	UPROPERTY(EditAnywhere)
	FSlateColor ThemeColorHover;
	UPROPERTY(EditAnywhere)
	FSlateColor ThemeColorExtra;
	UPROPERTY(EditAnywhere)
	FSlateFontInfo TextAndCaptionFont;
	UPROPERTY(EditAnywhere)
	FSlateColor TextAndCaptionColor;
	UPROPERTY(EditAnywhere)
	FSlateFontInfo TextHeaderFont;
	UPROPERTY(EditAnywhere)
	FSlateFontInfo TextFooterFont;
	UPROPERTY(EditAnywhere)
	FSlateColor TextHeaderColor;
	UPROPERTY(EditAnywhere)
	FSlateColor TextFooterColor;
	UPROPERTY(EditAnywhere)
	FSlateColor TextElementColor;
	UPROPERTY(EditAnywhere)
	FSlateFontInfo TextElementFont;
	UPROPERTY(EditAnywhere)
	FSlateColor BottomLineColor;
	UPROPERTY(EditAnywhere)
	FSlateFontInfo BottomLineFont;
	UPROPERTY(EditAnywhere)
	FSlateColor ToolTipBackgroundTint;
	UPROPERTY(EditAnywhere)
	UTexture* ToolTipBackgroundTexture;
	UPROPERTY(EditAnywhere)
	FVector2D ToolTipBackgroundSize;
	UPROPERTY(EditAnywhere)
	TEnumAsByte< ESlateBrushDrawType::Type> ToolTipBackgroundDrawAS;
	UPROPERTY(EditAnywhere)
	FMargin ToolTipBackgroundMargin;
	UPROPERTY(EditAnywhere)
	UTexture* DialogBackgroundTexture;
	UPROPERTY(EditAnywhere)
	FVector2D DialogBackgroundSize;
	UPROPERTY(EditAnywhere)
	TEnumAsByte< ESlateBrushDrawType::Type> DialogBackgroundDrawAs;
	UPROPERTY(EditAnywhere)
	FMargin DialogBackgroundMargin;
	UPROPERTY(EditAnywhere)
	FSlateColor DialogBackgroundTint;
	
};

USTRUCT(BlueprintType)
struct FNLTButtonData :public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UTexture* ImageTexture;
	UPROPERTY(EditAnywhere)
	FVector2D ImageSize;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESlateBrushDrawType::Type>DrawAsType;
	UPROPERTY(EditAnywhere)
	FMargin ImagePadding;
	UPROPERTY(EditAnywhere)
	FMargin PressPadding;
	UPROPERTY(EditAnywhere)
	FMargin NormalPadding;

	FSlateBrush ToSlateBrush() const
	{
		FSlateBrush Other;
		Other.Margin = ImagePadding;
		Other.SetResourceObject(ImageTexture);
		Other.DrawAs = DrawAsType;
		Other.ImageSize = ImageSize;
		return Other;
	}

	
};


USTRUCT(BlueprintType)
struct FNLTCheckBoxData :public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UTexture* CheckTexture;

	UPROPERTY(EditAnywhere)
	UTexture* UnCheckTexture;

	UPROPERTY(EditAnywhere)
	UTexture* UndeterminTexture;
	
	UPROPERTY(EditAnywhere)
	FVector2D ImageSize;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESlateBrushDrawType::Type>DrawAsType;
	
	UPROPERTY(EditAnywhere)
	FMargin NormalPadding;
	
};


USTRUCT(BlueprintType)
struct FNLTComboBoxData :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UTexture* ImageTexture;
	UPROPERTY(EditAnywhere)
	FVector2D ImageSize;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESlateBrushDrawType::Type>DrawAsType;
	UPROPERTY(EditAnywhere)
	FMargin NormalPadding;
	UPROPERTY(EditAnywhere)
	FMargin PressPadding;
	
	UPROPERTY(EditAnywhere)
	UTexture* ArrowTexture;
	UPROPERTY(EditAnywhere)
	FVector2D ArrowSize;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESlateBrushDrawType::Type>ArrowDrawAsType;
	UPROPERTY(EditAnywhere)
	FMargin ArrowPadding;

	UPROPERTY(EditAnywhere)
	UTexture* BorderTexture;
	UPROPERTY(EditAnywhere)
	FVector2D BorderSize;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESlateBrushDrawType::Type>BorderDrawAsType;
	UPROPERTY(EditAnywhere)
	FMargin BorderPadding;

	UPROPERTY(EditAnywhere)
	FMargin MenuBorderPadding;
	UPROPERTY(EditAnywhere)
	FSlateColor ItemBackgroundColor;
};

USTRUCT(BlueprintType)
struct FNLTSliderData :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UTexture* BarImage;
	UPROPERTY(EditAnywhere)
	FVector2D BarImageSize;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESlateBrushDrawType::Type>BarDrawAsType;
	UPROPERTY(EditAnywhere)
	FSlateColor BarNormalTint;
	UPROPERTY(EditAnywhere)
	FSlateColor BarDisabledTint;

	UPROPERTY(EditAnywhere)
	UTexture* ThumbImage;
	UPROPERTY(EditAnywhere)
	FVector2D ThumbImageSize;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESlateBrushDrawType::Type>ThumbDrawAsType;
	UPROPERTY(EditAnywhere)
	FSlateColor ThumbNormalTint;
	UPROPERTY(EditAnywhere)
	FSlateColor ThumbDisabledTint;
};

USTRUCT(BlueprintType)
struct FNLTTextInputData :public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UTexture* ImageTexture;
	UPROPERTY(EditAnywhere)
	FVector2D ImageSize;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESlateBrushDrawType::Type>DrawAsType;
	UPROPERTY(EditAnywhere)
	FMargin ImagePadding;
	UPROPERTY(EditAnywhere)
	FMargin Padding;
	
};

UENUM(BlueprintType)
enum EUIThemeDataType
{
	MiscData		,
	ButtonData		,
	CheckBoxData	,
	ComboBoxData	,
	SliderData		,
	TextInputData	
	
};