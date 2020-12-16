// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NLTCore.h"


#include "Core/NLTLog.h"
#include "RTTI/GlobalDispatcher.h"



UNLTCore::UNLTCore()
{
	ID = 0;
}

void UNLTCore::Init()
{
	Dispatcher = NewObject<UGlobalDispatcher>(this);
	Dispatcher->Init();

#if PLATFORM_WINDOWS
	BOOL status;
	DWORD readData;
	PWCHAR readMessage = nullptr;
	status = readDwordValueRegistry(HKEY_CURRENT_USER,TEXT("NLT"),TEXT("ID"),&readData);
	if(status == TRUE)
	{
		ID = readData;
		status = FALSE;
	}
	
	
	//ID 最后一位 记录 是否需要记住密码  
	if (ID > 0 && ID % 2)
	{
		status = readUserInfoFromRegistry(HKEY_CURRENT_USER, L"NLT", L"PassWord", &readMessage); //read string
		if (status != TRUE)
			MLBCoreLog(TEXT("Read PWD Failed Open Login ID UI"),false,ELogVerbosity::Warning);
		if (readMessage != nullptr)
		{
			Pwd = readMessage;
			print(TEXT(" PassWord = ") +  Pwd);
			free(readMessage);
			readMessage = nullptr;
		}
	}
#endif

}
