// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NLTUICore.h"

#include <string>



#include "EditorViewportClient.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Core/NLTGameInstance.h"
#include "Core/NLTLog.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/UIBuildHelpFunctionLibrary.h"

#define MAXIDNUM 6

void UNLTUICore::Init(UNLTGameInstance* GameInstance)
{
    //UITheme = NewObject<UMLBUITheme>(this);
    CreateBaseMainUI(GameInstance);
}

UBaseUI* UNLTUICore::BuildPwdConfirmUI(FBuildUIInfo BuildUIInfo, APlayerController* Controller,
    FOnClicked Ensure, FOnClicked Cancel,int64& ID,FString& Pwd)
{
    UBaseUI* ret = BuildUI<UMLBMainLoginUI>(BuildUIInfo,Controller,MLBMainLoginUIClass,MLBLoginThemeClass,Logintheme);
    verify(ret); 
    auto Lambda_ID =[&](const FText& IDText,ETextCommit::Type IDType)
    {
        if(IDType == ETextCommit::OnUserMovedFocus && ResultID.IsNumeric())
        {
            ResultID =IDText.ToString();
            int64 IDs = FPlatformString::Atoi64(*ResultID);
            ID = UpdateID(IDs);
            MLBCoreLog(TEXT("Login ID") + FString::FromInt(ID));
        }
        auto* editbox = Cast<UEditableTextBox>(IDParticalWidget->WidgetTree->FindWidget(TEXT("NLTInputText")));
        
        if (IDType == ETextCommit::Default)
        {
            const FRegexPattern RegexPattern(TEXT("^[1-9]*$"));
            FString String_ID= IDText.ToString();
            
            FRegexMatcher RegexMatcher(RegexPattern, String_ID);
            /*
            \* TODO:偏移2位,有一位结束符 判断为空,否则无法彻底删除
            */
            if ((RegexMatcher.FindNext() && /*String_ID.IsNumeric() &&*/ String_ID.GetCharArray().Num() < MAXIDNUM+2) || String_ID.IsEmpty())
            {
                ResultID =  String_ID;
            }
        }
        if (editbox)
        {
           editbox->SetText(FText::FromString(ResultID)); 
        }
    };

    auto Lambda_Pwd =[&](const FText& IDText,ETextCommit::Type IDType)
    {
        if(IDType == ETextCommit::OnUserMovedFocus)
            Pwd =IDText.ToString();

        if (IDType == ETextCommit::Default)
        {
            FString String_Pwd= IDText.ToString();
            
            if ( String_Pwd.GetCharArray().Num() < 2*MAXIDNUM || String_Pwd.IsEmpty())
            {
                Pwd =  String_Pwd;
            }
        }
        auto* editbox = Cast<UEditableTextBox>(PwdParticalWidget->WidgetTree->FindWidget(TEXT("NLTInputText")));
        
        if (editbox)
        {
            editbox->SetText(FText::FromString(Pwd)); 
        }
    };

    
    auto Lambda_Rmeb = [&](ECheckBoxState CheckBoxState)
    {
        if (CheckBoxState == ECheckBoxState::Checked)
            bRememberPwd = true;
        else
            bRememberPwd = false;
        
        
        ID = UpdateID(FCString::Atoi64(*ResultID));
    };

    
    FEditableTextStatChanged IDTextStatChanged ;
    FEditableTextStatChanged PwdTextStatChanged ;
    FCheckBoxStatChanged CheckBoxStatChanged;
    IDTextStatChanged.BindLambda(Lambda_ID);
    PwdTextStatChanged.BindLambda(Lambda_Pwd);
    CheckBoxStatChanged.BindLambda(Lambda_Rmeb);
    
    FBuildWidgetInfo BuildWidgetInfo_Remb;
    BuildWidgetInfo_Remb.SetID(FName(TEXT("BuildWidgetInfo_Remb")))
    .SetCaption(TEXT("KeepPassword"))
    .SetDelagate(CheckBoxStatChanged)
    .SetWidth(50.f)
    .SetPadding(600,50,0,0)
    .SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
    
    FBuildWidgetInfo BuildWidgetInfo_ID;
    BuildWidgetInfo_ID.SetID(FName(TEXT("PwdConfirm_ID")))
    .SetCaption(TEXT("ID              "))
    .SetWidth(50.f)
    .SetPadding(600,200,600,0)
    .SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center)
    .EventDelegate = IDTextStatChanged;
    
    
    FBuildWidgetInfo BuildWidgetInfo_Pwd;
    BuildWidgetInfo_Pwd.SetID(FName(TEXT("PwdConfirm_Pwd")))
    .SetCaption(TEXT("PassWord"))
    .SetWidth(50.f)
    .SetPadding(600,50,600,0)
    .SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center)
    .EventDelegate = PwdTextStatChanged;
   

    FBuildWidgetInfo BuildWidgetInfo_Ensure;
    
    BuildWidgetInfo_Ensure.Caption = FText::FromString(TEXT("Ensure"));
    //BuildWidgetInfo_Ensure.Tooltip = FText::FromString(TEXT(""))
    BuildWidgetInfo_Ensure.EventDelegate = Ensure;
    BuildWidgetInfo_Ensure.SetID(FName(TEXT("Login_Ensure")));
     
    FBuildWidgetInfo BuildWidgetInfo_Cancel;
    BuildWidgetInfo_Cancel.Caption = FText::FromString(TEXT("Cancel"));
    BuildWidgetInfo_Cancel.ID = FName(TEXT("Login_Cancel"));
    BuildWidgetInfo_Cancel.EventDelegate = Cancel;


    FBuildWidgetInfo BuildWidgetInfo_RowButton;
    BuildWidgetInfo_RowButton.Padding =FMargin(0,150,0,0);
    BuildWidgetInfo_RowButton.HorizontalAlignment =EHorizontalAlignment::HAlign_Fill;
    BuildWidgetInfo_RowButton.VerticalAlignment = EVerticalAlignment::VAlign_Center;
    BuildWidgetInfo_RowButton.ID = FName(TEXT("RowButton_LoginRowButton"));
    
    TArray<FBuildWidgetInfo>RowButtonsBuildInfos;
    RowButtonsBuildInfos.SetNum(2);
    RowButtonsBuildInfos[0] =BuildWidgetInfo_Ensure;
    RowButtonsBuildInfos[1] =BuildWidgetInfo_Cancel;
    
    TArray<UParticalWidget*>RowButtons;
  
    UUIBuildHelpFunctionLibrary::AddEditableTextBox(this,ret,IDParticalWidget,BuildWidgetInfo_ID
        ,500,FText::FromString(TEXT("Input ID")));

    UUIBuildHelpFunctionLibrary::AddEditableTextBox(this,ret,PwdParticalWidget,BuildWidgetInfo_Pwd
        ,500,FText::FromString(TEXT("Input PassWord")));

    auto* PwdEditbox = Cast<UEditableTextBox>(PwdParticalWidget->WidgetTree->FindWidget(TEXT("NLTInputText")));
    if (PwdEditbox)
    {
        print(TEXT("Set pass word Success"));
        PwdEditbox->SetIsPassword(true);
    }
    
    UUIBuildHelpFunctionLibrary::AddCheckBox(this,ret,CheckBoxParticalWidget,BuildWidgetInfo_Remb,50,false);
    
    UUIBuildHelpFunctionLibrary::AddRowButtons(this,ret,RowButtonsBuildInfos,BuildWidgetInfo_RowButton,0.f,15.f,RowButtons);
    return ret;
}


void UNLTUICore::StartBuildAllUI(TArray<FBuildUIInfo> AllBuildUIInfos,APlayerController* Controller,UMLBMainLoginUI* &OutMLBMainLoginUI,UMLB_MainUI* &OutMLBMainUI,UMLB_SettingUI* &OutUMLB_SettingUI)
{
    
    for (const FBuildUIInfo& m : AllBuildUIInfos)
    {
        switch (m.UIType)
        {
        case Login:
            {
                if (!MLBMainLoginUIClass|| !MLBLoginThemeClass)
                    return;
                MLB_LoginUI = BuildUI<UMLBMainLoginUI>(m,Controller,MLBMainLoginUIClass,MLBLoginThemeClass,Logintheme);
                MLB_LoginUI->UICore = this;
                if(!MLB_LoginUI->ContentBox)
                    return;
                OutMLBMainLoginUI= MLB_LoginUI;
                
                /*MLB_LoginUI = CreateUI<UMLBMainLoginUI>(Controller);
                MLB_LoginUI->UICore = this;
                MLB_LoginUI->Info = m;
                AddWidgetToMainUI(MLB_LoginUI);
                Logintheme = NewObject<UMLBUITheme>(this);

                Logintheme->SetTheme(m.UITheme);*/
            }
            break;
        case Main:
            {
                /*
                *\
                *  主UI 在进入游戏后一直存在
                *\
                */
                if (!MLB_MainUIClass || !MLBMainThemeClass)
                    return;
                UGameInstance* Instance = UGameplayStatics::GetGameInstance(this);
                MLB_MainUI = BuildUI<UMLB_MainUI>(m,Instance,MLB_MainUIClass,MLBMainThemeClass,Maintheme);
            
                if (MLB_MainUI->ContentBox == nullptr)
                {
                    //MLB_MainUI->TakeWidget();
                    return;
                }
                check(Maintheme);
                MLB_MainUI->UICore = this;
                //MLB_MainUI->Initialize();
                OutMLBMainUI = MLB_MainUI;
            }
            break;
        case Setting:
            {
                if (!MLB_SettingUIClass ||!MLBSettingThemeClass)
                    return;
                MLB_SettingUI = BuildUI<UMLB_SettingUI>(m,Controller,MLB_SettingUIClass,MLBSettingThemeClass,Settingtheme);
                MLB_SettingUI->UICore = this;
                OutUMLB_SettingUI = MLB_SettingUI;
            }
            break;
        default: ;
        }
    }
    
}

void UNLTUICore::AddWidgetToMainUI(UWidget* UI)const
{
    
    if (WrapMainUI)
    {
        WrapMainUI->TakeWidget();
        //WrapMainUI->Initialize();
        
        WrapMainUI->WidgetSwitcher->AddChild(UI);
       
        if (!WrapMainUI->WidgetSwitcher->IsVisible())
        {
            WrapMainUI->WidgetSwitcher->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

int64 UNLTUICore::UpdateID(int64 m_ID)
{
    int64 ret = 0;
    if (FString::FromInt(m_ID).GetCharArray().Num() == MAXIDNUM+1)
    {
        ret = 10* m_ID + bRememberPwd;
    }
    else if (FString::FromInt(m_ID).GetCharArray().Num() == MAXIDNUM+2)
    {
        m_ID = FMath::Floor( m_ID / 10);
        ret = m_ID*10 + bRememberPwd;
    }
    print(FString::FromInt(ret));
    return ret;
}

void UNLTUICore::CreateBaseMainUI(UGameInstance* GameInstance)
{
    //WrapMainUI = CreateWidget<UMainUI>(GameInstance);
    WrapMainUI = CreateUI<UMainUI>(GameInstance,UMainUI::StaticClass());
    //WrapMainUI->AddToViewport();
   
}

void UNLTUICore::ShowUI() const
{
    WrapMainUI->AddToViewport();
}
