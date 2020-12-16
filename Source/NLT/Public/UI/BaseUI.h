// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MLBUITheme.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Core/NLTDataTypes.h"

#include "BaseUI.generated.h"

/**
 * 
 */
UCLASS()
class NLT_API UBaseUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UBaseUI(const FObjectInitializer& ObjectInitializer);


	virtual void NativeOnInitialized()override;
	//在UMG中预览但是在树中任然无法查看到变量
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	//Build UI Them and Column
	FBuildUIInfo Info;
	
	
	UPROPERTY()
	UNLTUICore* UICore;
	
	//构建UI风格
	void BuildColumn();
	void CreateColumn(float ColumnDistance , float Width = 1.f);
	//设置UI屏幕占比
	void SetScaleInScreen(FVector2D ScaleSize);
	//
	void SetBackGroundImage(UTexture* BackGround);
	//添加UI
	UPanelSlot* AddElement(UParticalWidget* ParticalWidget,EVerticalAlignment VerticalAlignment);
	//记录在案
	void RegisterElement(UParticalWidget* Element);

	//获取menu添加内容
	UParticalWidget* GetMenuWidget()
	{
		return AllMenuWidget[CurrentMenuWidget] != nullptr ? AllMenuWidget[CurrentMenuWidget] : nullptr;
	}
	//确定当前添加内容的区块
	// ---- 无需选择
	// --|-- 0在左 ，1在右
	// -|-|- 0   1   2  
	void SetMenuWidgetIndex(uint8 Index){CurrentMenuWidget = Index;}	
	//主要内容
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta =(BindWidget))
	UHorizontalBox* ContentBox;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta =(BindWidget))
	UVerticalBox* HeaderVerticalBox;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta =(BindWidget))
	UVerticalBox* FooterVerticalBox;
	//Wrap
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta =(BindWidget))
	UPanelWidget* MenuContenBox;
	//Vertical Box Content
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta =(BindWidget))
	UVerticalBox* MenuVerticalBox;
	//背景图
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta =(BindWidget))
	UImage* BGImage;
	//黑色背景_内容以外区域
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta =(BindWidget))
	UImage* DarkBGImage;

	UFUNCTION(BlueprintPure,Category = BaseUI)
	TEnumAsByte<EUIType> GetBaseUIType()const{return Info.UIType;}
	
private:
	UPROPERTY()
	TArray<UParticalWidget*>AllParticalWidget;
	UPROPERTY()
	TArray<UParticalWidget*>AllMenuWidget;

	TArray<int32>ElementCounts;
	uint8 CurrentMenuWidget = 0;
};
