// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "RTTI/AnyType.h"
#include "UObject/ObjectMacros.h"


#include "NLTDataTypes.generated.h"

/**
 * 
 */


#define NoneString TEXT("")

UENUM(BlueprintType)
enum EUIColumn
{
    Column_One    UMETA(DisplayName = "----"),
    Column_Two    UMETA(DisplayName = "-|-"),
    Column_Three    UMETA(DisplayName = "-|--"),
    Column_Four    UMETA(DisplayName = "--|-"),
    Column_Five    UMETA(DisplayName = "-|-|-")
};

UENUM(BlueprintType)
enum EUITheme
{
    Normal    UMETA(DisplayName = "ordinary"),
    
    Rounded    UMETA(DisplayName = "round corner"),
    
    loveliness    UMETA(DisplayName = "KAWAYI")
};

UENUM(BlueprintType)
enum EUIType
{
    Login    ,
    
    Main    ,
    
    Setting    
};

//应用到UI颜色类型
UENUM(BlueprintType)
enum class EUIColorType :uint8
{
    Normal    ,
    Hover    ,
    Extra    ,
    Font    ,
    Header    ,
    Footer    ,
    Element
};

USTRUCT(BlueprintType)
struct FBuildUIInfo
{
    GENERATED_BODY()
    FBuildUIInfo()
    {
        ColumnDistance = 20.f;
        Width = .75f;
        Height = .75f;
        UIType = EUIType::Login;
        UIColumn = EUIColumn::Column_One;
        UITheme = EUITheme::Normal;
        Padding = FMargin(100.f);
        bAutoSpacing = false;
    }
    
    
    // Not Use To Column_One
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float ColumnDistance;
    //Width Scale
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float Width;
    //Height Scale
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float Height;
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TEnumAsByte<EUIType> UIType;
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TEnumAsByte<EUIColumn> UIColumn;
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TEnumAsByte<EUITheme> UITheme;
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FMargin Padding;
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    bool bAutoSpacing;

    //内容以外部分是否黑色覆盖
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    bool bShowDarkBG;
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    UTexture* BackgroundTexture;
    
    
};



USTRUCT(BlueprintType)
struct FBuildWidgetInfo
{
    GENERATED_BODY()
    /*FBuildWidgetInfo()=default;
    FBuildWidgetInfo operator=(FBuildWidgetInfo Info)=default;*/
    /*FBuildWidgetInfo(FBuildWidgetInfo Info)
        : VerticalAlignment(Info.VerticalAlignment),
        HorizontalAlignment(Info.HorizontalAlignment)
    {
       
    }*/

    FBuildWidgetInfo()
        : VerticalAlignment(EVerticalAlignment::VAlign_Center)
          , HorizontalAlignment(EHorizontalAlignment::HAlign_Center)
          , Width(-1)
          , PressSoundBase(nullptr)
          , ExtraSoundBase(nullptr)
          , bUseDispacher(false)
    {
    }

    /*FBuildWidgetInfo(FBuildWidgetInfo Other)
    :       ID(Other.ID)
          , Caption(Other.Caption)
          , Tooltip(Other.Tooltip)
          , Padding(Other.Padding)
          , VerticalAlignment(Other.VerticalAlignment)
          , HorizontalAlignment(Other.HorizontalAlignment)
          , PressSoundBase(Other.PressSoundBase)
          , ExtraSoundBase(Other.ExtraSoundBase)
          , EventDelegate(Other.EventDelegate)
          , bUseDispacher(Other.bUseDispacher)
    {}*/

    FBuildWidgetInfo(FBuildWidgetInfo& Other)
        : ID(Other.ID)
          , Caption(Other.Caption)
          , Tooltip(Other.Tooltip)
          , Padding(Other.Padding)
          , VerticalAlignment(Other.VerticalAlignment)
          , HorizontalAlignment(Other.HorizontalAlignment)
          , Width(-1)
          , PressSoundBase(Other.PressSoundBase)
          , ExtraSoundBase(Other.ExtraSoundBase)
          , EventDelegate(Other.EventDelegate)
          , bUseDispacher(Other.bUseDispacher)
    {
    }

    FBuildWidgetInfo(const FBuildWidgetInfo& Other)
    :  ID(Other.ID)
       , Caption(Other.Caption)
       , Tooltip(Other.Tooltip)
       , Padding(Other.Padding)
       , VerticalAlignment(Other.VerticalAlignment)
       , HorizontalAlignment(Other.HorizontalAlignment)
        , Width(-1)
       , PressSoundBase(Other.PressSoundBase)
       , ExtraSoundBase(Other.ExtraSoundBase)
       , EventDelegate(Other.EventDelegate)
       , bUseDispacher(Other.bUseDispacher)
    {}

    bool operator==(FBuildWidgetInfo Info)const
    {
        return Info.ID==ID;
    }
    
    
    //小部件ID  不可重复 
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FName ID;
    FBuildWidgetInfo& SetID(FName in_ID)
    {
        ID = in_ID;
        return *this;
    }
    //短小  直接拷贝
    FBuildWidgetInfo& SetID(FString in_ID)
    {
        ID =FName(in_ID);
        return *this;
    }
    
    //标题
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FText Caption;
    FBuildWidgetInfo& SetCaption(const FText& in_Caption)
    {
        Caption = in_Caption;
        return *this;
    }

    FBuildWidgetInfo& SetCaption(const FString& in_Caption)
    {
        Caption =FText::FromString( in_Caption);
        return *this;
    }
    
    //介绍
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FText Tooltip;

    FBuildWidgetInfo& SetTooltip(const FText& in_Tooltip)
    {
        Caption = in_Tooltip;
        return *this;
    }

    
    FBuildWidgetInfo& SetTooltip(const FString& in_Tooltip)
    {
        Tooltip =FText::FromString( in_Tooltip);
        return *this;
    }
    
    //
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FMargin Padding;
    FBuildWidgetInfo& SetPadding(FMargin in_Padding)
    {
        Padding = in_Padding;
        return *this;
    }

    FBuildWidgetInfo& SetPadding(float Left,float Top ,float Right ,float Buttom)
    {
        Padding = FMargin(Left,Top,Right,Buttom);
        return *this;
    }
    
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TEnumAsByte< EVerticalAlignment>VerticalAlignment;
    FBuildWidgetInfo& SetVerticalAlignment(TEnumAsByte< EVerticalAlignment> VA)
    {
        VerticalAlignment = VA;
        return *this;
    }
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TEnumAsByte<EHorizontalAlignment>HorizontalAlignment;
    FBuildWidgetInfo& SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> HA)
    {
        HorizontalAlignment = HA;
        return *this;
    }
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float Width;
    FBuildWidgetInfo& SetWidth(float Wd)
    {
        Width = Wd;
        return *this;
    }
    //Button
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    USoundBase* PressSoundBase;
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    USoundBase* ExtraSoundBase;


    //////////////////////
    ///Only CPP 
    AnyType EventDelegate;
    FBuildWidgetInfo& SetDelagate(const AnyType& Delegate)
    {
        EventDelegate = Delegate;
        return *this;
    }
    bool bUseDispacher;
    
};

using FCheckBoxStatChanged = TDelegate<void(ECheckBoxState)>;
using FSliderStatChanged = TDelegate<void(float)>;
using FComboBoxStatChanged= TDelegate<void(FString,ESelectInfo::Type)>;
using FEditableTextStatChanged = TDelegate<void(const FText&,ETextCommit::Type)>;
UCLASS()
class UNLTDataTypes : public UObject
{
    GENERATED_BODY()
public:
    
};
