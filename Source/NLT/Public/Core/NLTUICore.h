// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <cassert>


#include "NLTDataTypes.h"
#include "GamePlay/NLTPlayerController.h"
#include "UI/MainUI.h"
#include "UI/MLBMainLoginUI.h"
#include "UI/MLBUITheme.h"
#include "UI/MLB_MainUI.h"
#include "UI/MLB_SettingUI.h"
#include "UI/ParticalWidget.h"
#include "UObject/NoExportTypes.h"
#include "NLTUICore.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NLT_API UNLTUICore : public UObject
{
	GENERATED_BODY()

public:
    void Init(class UNLTGameInstance* GameInstance);

    class UBaseUI* BuildPwdConfirmUI(FBuildUIInfo BuildUIInfo ,APlayerController* Controller,FOnClicked Ensure,FOnClicked Cancel,int64& ID,FString& Pwd);
    
   
    //UI Build Origin
    UFUNCTION(BlueprintCallable,Category=UICore)
    void StartBuildAllUI(TArray<FBuildUIInfo>AllBuildUIInfos,APlayerController* Controller,UMLBMainLoginUI* &MLBMainLoginUI,UMLB_MainUI* &MLBMainUI,UMLB_SettingUI* &UMLB_SettingUI);
     
    void CreateBaseMainUI(UGameInstance* GameInstance);

    void ShowUI() const;
    //添加到主显示UI
    void AddWidgetToMainUI(UWidget* UI)const;
    //切换显示
    UFUNCTION(BlueprintCallable,Category=UICore)
    void ActiveWidget(UBaseUI* BaseUI)const
    {
        WrapMainUI->SwtichUI(BaseUI);
    }
    UFUNCTION(BlueprintPure,Category=UICore)
    UMLBUITheme* GetUITheme(TEnumAsByte<EUIType> Type)
    {
        switch (Type)
        {
          case EUIType::Login: return Logintheme;
          case EUIType::Main: return Maintheme;
          case EUIType::Setting: return Settingtheme;
        }
        return nullptr;
    }
    UPROPERTY()
    UMLBUITheme* UITheme;
    UPROPERTY(EditDefaultsOnly,Category=UICore)
    TMap<EWidgetType,TSubclassOf<UParticalWidget>>ChildWidgets;
    UPROPERTY(EditDefaultsOnly,Category=UICore)
    TSubclassOf<UMLBUITheme>MLBLoginThemeClass;
    UPROPERTY(EditDefaultsOnly,Category=UICore)
    TSubclassOf<UMLBUITheme>MLBMainThemeClass;
    UPROPERTY(EditDefaultsOnly,Category=UICore)
    TSubclassOf<UMLBUITheme>MLBSettingThemeClass;
    UPROPERTY(EditDefaultsOnly,Category=UICore)
    TSubclassOf<UMLBMainLoginUI>MLBMainLoginUIClass;
    UPROPERTY(EditDefaultsOnly,Category=UICore)
    TSubclassOf<UMLB_MainUI>MLB_MainUIClass;
    UPROPERTY(EditDefaultsOnly,Category=UICore)
    TSubclassOf<UMLB_SettingUI>MLB_SettingUIClass;

    UPROPERTY(BlueprintReadOnly,Category = UICore)
    UMainUI* WrapMainUI;
 private:
    UPROPERTY()
    UMLBUITheme* Logintheme;

    UPROPERTY()
    UMLBUITheme* Maintheme;
    
    UPROPERTY()
    UMLBUITheme* Settingtheme;
    
    
    UPROPERTY()
    UMLBMainLoginUI* MLB_LoginUI;
    UPROPERTY()
    UMLB_SettingUI* MLB_SettingUI;
    UPROPERTY()
    UMLB_MainUI* MLB_MainUI;
    UPROPERTY()
    ANLTPlayerController* OwingController;
    UPROPERTY()
    UGameInstance* OwingGameInstance;


    ///////////////////////////////////
    ///Confirm Pwd
    ///////////////////////////////////
    UPROPERTY()
    UParticalWidget* IDParticalWidget ;
    UPROPERTY()
    UParticalWidget* PwdParticalWidget ;
    UPROPERTY()
    UParticalWidget* CheckBoxParticalWidget ;
    bool bRememberPwd = false;
    FString ResultID;
    int64 UpdateID(int64 m_ID);


















    ///////////////////////////////////////
    ///
    ///
    template<typename U,typename UMLBUITheme,typename UClass,typename ThemeClass>
   U* BuildUI(FBuildUIInfo m,APlayerController* Controller,UClass Class,ThemeClass m_themeclass,UMLBUITheme* &UITheme)
    {
        auto* ui = CreateUI<U>(Controller,Class);
        ui->UICore = this;
        ui->Info = m;
        
        AddWidgetToMainUI(ui);
        UITheme = NewObject<UMLBUITheme>(this,m_themeclass);
        UITheme->SetTheme(m.UITheme);
        return ui;
    }

    template<typename U,typename UMLBUITheme,typename UClass,typename ThemeClass>
    U* BuildUI(FBuildUIInfo m,UGameInstance* Controller,UClass Class,ThemeClass m_themeclass,UMLBUITheme* &UITheme)
    {
        auto* ui = CreateUI<U>(Controller,Class);
        ui->UICore = this;
        ui->Info = m;
    
        AddWidgetToMainUI(ui);
        UITheme = NewObject<UMLBUITheme>(this,m_themeclass);
        UITheme->SetTheme(m.UITheme);
        return ui;
    }
    
    template<typename T>
    T* CreateUI(UGameInstance* GameInstance,TSubclassOf<UUserWidget> UserWidgetClass = T::StaticClass())
    {
        return CreateWidget<T>(GameInstance,UserWidgetClass); 
    }

    template<typename T = UBaseUI>
    T* CreateUI(APlayerController* Controller,TSubclassOf<UUserWidget> UserWidgetClass = T::StaticClass())
    {
        return CreateWidget<T>(Controller,UserWidgetClass);
    }
    template<typename T>
    T* CreateUI(UWidget* Widget);
};



/*
template <typename U,typename  UMLBUITheme,typename UClass,typename ThemeClass>
U* UNLTUICore::BuildUI(FBuildUIInfo m,APlayerController* Controller ,UClass Class ,UMLBUITheme*  &UITheme)
{ 
    auto* ui = CreateUI<U>(Controller,Class);
    ui->UICore = this;
    ui->Info = m;
    
    AddWidgetToMainUI(ui);
    UITheme = NewObject<UMLBUITheme>(this,MLBUIThemeClass);
    UITheme->SetTheme(m.UITheme);
    return ui;
}
*/

/*template <typename T>
T* UNLTUICore::CreateUI(UGameInstance* GameInstance)
{
   return CreateWidget<T>(GameInstance); 
}*/


/*
template <typename T,typename CLASS = UClass>
T* UNLTUICore::CreateUI(APlayerController* Controller,TSubclassOf<UUserWidget> UserWidgetClass = T::StaticClass())
{
    if (u_class)
    {
        return  CreateWidget<T>(Controller,u_class); 
    }
    return CreateWidget<T>(Controller); 
}
*/

template <typename T>
T* UNLTUICore::CreateUI(UWidget* Widget)
{
    return CreateWidget<T>(Widget); 
}