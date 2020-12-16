// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class NLT_API UMainUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UMainUI(const FObjectInitializer& ObjectInitializer);
	//在UMG中预览但是在树中任然无法查看到变量
	virtual void NativePreConstruct()override;
	//Just Build In Run Time
	virtual void NativeConstruct() override;

	
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
	UPROPERTY(BlueprintReadWrite/*,Category = MainUI*/)
	UWidgetSwitcher* WidgetSwitcher;
	UPROPERTY()
	UPanelWidget* RootWidgetS = nullptr;
	virtual bool Initialize()override;
	virtual void SetContentForSlot(FName SlotName, UWidget* Content) override;
	void SwtichUI(int8 ActiveIndex);
	void SwtichUI(UWidget* ActiveWidget);
};
