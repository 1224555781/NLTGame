// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Core/NLTDataTypes.h"
#include "GameFramework/PlayerController.h"
#include "RTTI/AnyType.h"

#if UE_SERVER && PLATFORM_LINUX
#include "jdbc/mysql_driver.h"
//#include "mysql.h"
#include "jdbc/mysql_connection.h"
#include "mysql.h"
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <mysqlx/xdevapi.h>
#endif


#include "Core/NLTLog.h"



#include "NLTPlayerController.generated.h"



/**
 * 
 */
UCLASS()
class NLT_API ANLTPlayerController : public APlayerController
{
	GENERATED_BODY()
	ANLTPlayerController();
public:
	virtual void BeginPlay()override;
    //virtual void Tick(float DeletaSeconds)override;
	virtual void Tick( float DeltaSeconds)override;

	UFUNCTION(BlueprintCallable,Category = NLTController)
	void StartBuildUI_Test();
protected:
	UPROPERTY(EditDefaultsOnly,Category= NLTController)
	TArray<FBuildUIInfo>AllInfo;


	
	
	/**
	 * 
	 * Login Func And Param 
	 */
	
	//密码验证
	UFUNCTION(Server,Reliable,WithValidation,Category = Login)
	void Server_VerifyPwd(int64 i_ID);

	//验证失败
	UFUNCTION(Client,Reliable,Category= Login)
	void Client_PwdVerifyFailed();
	//验证成功
	UFUNCTION(Client,Reliable,Category= Login)
    void Client_PwdVerifySuccess();

	void EnterGameLevel();
	
	void BuildSelectRoleUI();

	class UBaseUI* BuildPwdConfirmUI();
	
	void ShowInputPwdUI();

	UFUNCTION(BlueprintCallable,Category = Login)
	void BuildConfirmPwdUI(FBuildUIInfo Info);
	
	FOnClicked LoginEnsureClicked;
	FOnClicked LoginCancelClicked;
private:
	UPROPERTY()
	class UParticalWidget* RegisterButton = nullptr;
	void ButtonClickedCallBack(const AnyType& parm);


	
	UPROPERTY()
	class UMLB_MainUI* MainUI;
	UPROPERTY()
	class UMLB_SettingUI* SettingUI;
	UPROPERTY()
	class UMLBMainLoginUI* LoginUI;


	int64 ID;
	FString Pwd;
	








#if  UE_SERVER
	bool QureyPwd(int64 i_ID,const char* m_Pwd)
	{
		using namespace std;

		bool Ret =false;
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;
		sql::PreparedStatement* pstmt;

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1", "mysql", "Wj123456...");
		if (!con->isValid())
		{
			MLBCoreLog(TEXT("Connect SQL Falied"),false,ELogVerbosity::Error);
			return false;
		}
			/* Connect to the MySQL test database */
		con->setSchema("NLT");


		
		/* Select in ascending order */
		pstmt = con->prepareStatement("SELECT ID,Pwd FROM MLB ORDER BY ID ASC");
		res = pstmt->executeQuery();

		/* Fetch in reverse = descending order! */
		res->afterLast();
		while (res->previous())
		{
			Ret = m_Pwd == res->getString("ID");
			if (Ret)
				break;
		}
		delete res;

		delete pstmt;
		delete con;

		
		
	}


	bool RegsterID(int64 m_ID,const char* m_Pwd)
	{
		bool Ret =false;
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;
		sql::PreparedStatement* pstmt;
		using namespace ::mysqlx;
		
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1", "mysql", "Wj123456...");

		if (!con->isValid())
		{
			MLBCoreLog(TEXT("Connect SQL Falied"),false,ELogVerbosity::Error);
			return false;
		}
		/* Connect to the MySQL test database */
		con->setSchema("NLT");


		/* '?' is the supported placeholder syntax */
		pstmt = con->prepareStatement("INSERT INTO MLB(ID,Pwd) VALUES (?)");
		
		pstmt->setInt(pstmt->getMaxRows() +1,ID);
		pstmt->setString(pstmt->getMaxRows() +1,m_Pwd);
		//pstmt->setInt(,)
		pstmt->executeUpdate();
		
		delete pstmt;
		return true;
	}
#endif
};




