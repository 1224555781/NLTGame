// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/NLTPlayerController.h"
#include <functional>


#include "ISettingsModule.h"
#include "NetworkMessage.h"
#include "Core/NLTLog.h"
#include "Kismet/GameplayStatics.h"
#include "RTTI/GlobalDispatcher.h"
#include "UI/UIBuildHelpFunctionLibrary.h"
#include "Util/NLTUtilityFunctionLibrary.h"


ANLTPlayerController::ANLTPlayerController()
{
	
}

void ANLTPlayerController::BeginPlay()
{
	
	Super::BeginPlay();
	UUIBuildHelpFunctionLibrary::ShowUI(this);
	if(UNLTUtilityFunctionLibrary::GetNLTCore(this)->bNeedRmbPwd && !HasAuthority())
		ID = UNLTUtilityFunctionLibrary::GetNLTCore(this)->GetID();
	
	if(ID > 0 && HasAuthority())
		Server_VerifyPwd(ID);

	

}

void ANLTPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void ANLTPlayerController::StartBuildUI_Test()
{
	
	
	FBuildWidgetInfo WidgetInfo;
	FBuildWidgetInfo CheckBoxWidgetInfo;
	FBuildWidgetInfo ComboBoxWidgetInfo;

	
	CheckBoxWidgetInfo.ID = FName(TEXT("MLB"));
	CheckBoxWidgetInfo.Caption = FText::FromString(TEXT("MLB996"));
	CheckBoxWidgetInfo.Tooltip = FText::FromString(TEXT("MLB996"));
	CheckBoxWidgetInfo.bUseDispacher =true;
	
	FOnClicked RegisterButtonClicked;
	RegisterButtonClicked.BindLambda([]()->FReply
	{
		print(TEXT("I FEEL SO GOOD"));
		return FReply::Handled();
	});
	WidgetInfo.ID = FName(TEXT("RegisterButton"));
	WidgetInfo.Caption = FText::FromString(TEXT("CPPBUTTON"));
	WidgetInfo.Tooltip = FText::FromString(TEXT("CPPBUTTON"));
	WidgetInfo.EventDelegate = RegisterButtonClicked;
	UParticalWidget* CheckBox= nullptr;
	UUIBuildHelpFunctionLibrary::GetUICore(this)->StartBuildAllUI(AllInfo,this,LoginUI,MainUI,SettingUI);
	UUIBuildHelpFunctionLibrary::AddButton(this,MainUI,RegisterButton,WidgetInfo,0);
	UUIBuildHelpFunctionLibrary::AddCheckBox(this,MainUI,CheckBox,CheckBoxWidgetInfo,0);
	UParticalWidget* ComboBox= nullptr;
	ComboBoxWidgetInfo.ID = FName(TEXT("MLB_ComboBox"));
	ComboBoxWidgetInfo.Caption = FText::FromString(TEXT("MyComboBox"));
	ComboBoxWidgetInfo.Tooltip = FText::FromString(TEXT("MyComboBox"));
	ComboBoxWidgetInfo.Padding = FMargin(0,50,0,0);
	FComboBoxStatChanged ComboBoxStatChanged;
	ComboBoxStatChanged.BindLambda([](FString item,ESelectInfo::Type type)
	{
		print(TEXT("Current Select : ") +item);
	});
	ComboBoxWidgetInfo.EventDelegate = ComboBoxStatChanged;
	TArray<FString>Options{TEXT("MLB1"),TEXT("MLB2"),TEXT("MLB3")};
	UUIBuildHelpFunctionLibrary::AddComboBox(this,MainUI,ComboBox,ComboBoxWidgetInfo,0,Options,TEXT("MLB3"),ETextJustify::Left);

	UUIBuildHelpFunctionLibrary::GetUICore(this)->ActiveWidget(MainUI);
	UNLTUtilityFunctionLibrary::GetDispatcher(this)->AddListener_Implement_CPP(CheckBoxWidgetInfo.ID.ToString()
		,std::bind(&ANLTPlayerController::ButtonClickedCallBack,this,std::placeholders::_1),EDispachOpportunity::Directly);
}

void ANLTPlayerController::Server_VerifyPwd_Implementation(int64 m_ID)
{
	
}

bool ANLTPlayerController::Server_VerifyPwd_Validate(int64 m_ID){return true;}


void ANLTPlayerController::Client_PwdVerifyFailed_Implementation()
{
	
}

void ANLTPlayerController::Client_PwdVerifySuccess_Implementation()
{
}

void ANLTPlayerController::EnterGameLevel()
{
	
}

void ANLTPlayerController::BuildSelectRoleUI()
{
	
}

UBaseUI* ANLTPlayerController::BuildPwdConfirmUI()
{
	
	return  nullptr;
}

void ANLTPlayerController::ShowInputPwdUI()
{
	
}

void ANLTPlayerController::BuildConfirmPwdUI(FBuildUIInfo Info)
{
	LoginEnsureClicked.BindLambda([&]()->FReply
	{
		MLBCoreLog(TEXT("**************************"));
		MLBCoreLog(TEXT("*******Try To Login******"));
		MLBCoreLog(FString::Printf(TEXT("ID : %lld ,Pwd : %s"),ID,*Pwd));
		MLBCoreLog(TEXT("**************************"));
		
		return FReply::Handled();
	});

	LoginCancelClicked.BindLambda([&]()->FReply
	{
		UKismetSystemLibrary::QuitGame(this,this,EQuitPreference::Quit,true);
		//exit(0);
		return FReply::Handled();
	});
	UUIBuildHelpFunctionLibrary::GetUICore(this)->BuildPwdConfirmUI(Info,this,LoginEnsureClicked,LoginCancelClicked,ID,Pwd);
}

void ANLTPlayerController::ButtonClickedCallBack(const AnyType& parm)
{
	print(TEXT("I FEEL SO GOOD"));
}


