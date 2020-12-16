// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <stdexcept>

#include "UObject/NoExportTypes.h"
#if PLATFORM_WINDOWS
#include "windows/MinWindows.h"
#endif

#include "NLTCore.generated.h"

class UGlobalDispatcher;
#define TOTAL_BYTES_READ    1024
#define OFFSET_BYTES 1024

/**
 * 
 */
UCLASS()
class NLT_API UNLTCore : public UObject
{
	GENERATED_BODY()

	UNLTCore();
public:
	void Init();

	UGlobalDispatcher* GetDispatcher()const {return Dispatcher;}

    int64 GetID()
	{
        if (ID>0)
            ID =FMath::Floor( ID / 10);
	    else
	        ID = 0;
	    return ID;
	}
    FString GetPwd()const{return Pwd;}

    //判断是否需要自动登录
    uint8 bNeedRmbPwd    :1; 
private:
	UGlobalDispatcher* Dispatcher;


    
    /**
     * @ 缓存 账号密码以及是否需要自动登录
     */
    int64 ID;
    FString Pwd;
    
    //
    
    
#if PLATFORM_WINDOWS

    class RegistryError : public std::runtime_error
    {
    public:
        RegistryError(const char* message, LONG errorCode)
        : std::runtime_error{message}
          , m_errorCode{errorCode}
        {}

        LONG ErrorCode() const noexcept
        {
            return m_errorCode;
        }
      private:
        LONG m_errorCode;
    };


std::wstring RegGetDword(HKEY hKey,const std::wstring& subKey,const std::wstring& value)
{
    
    std::wstring data;
    DWORD dataSize{};
    LONG retCode = ::RegGetValue(
          hKey,
  subKey.c_str(),
    value.c_str(),
    RRF_RT_REG_SZ,
  nullptr,
    nullptr,
    &dataSize
);
    verifyf(retCode == ERROR_SUCCESS,TEXT("Get Value Failed From Regedit"));
    
    data.resize(dataSize / sizeof(wchar_t));
    LONG retCode2 = ::RegGetValue(
          hKey,
  subKey.c_str(),
    value.c_str(),
    RRF_RT_REG_DWORD,
    nullptr,
           &data[0],
    &dataSize
    );
    
    verifyf(retCode2 == ERROR_SUCCESS,TEXT("Get Value Failed From Regedit"));

    DWORD stringLengthInWchars = dataSize / sizeof(wchar_t);
    stringLengthInWchars--; // Exclude the NUL written by the Win32 API
    data.resize(stringLengthInWchars);
    return data;
}    
//Create key in registry
BOOL CreateRegistryKey(HKEY hKeyParent,PWCHAR subkey)
{
    DWORD dwDisposition; //It verify new key is created or open existing key
    HKEY  hKey;
    DWORD Ret;
    Ret =
        RegCreateKeyEx(
            hKeyParent,
            subkey,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &hKey,
            &dwDisposition);
    if (Ret != ERROR_SUCCESS)
    {
        return FALSE;
    }
    RegCloseKey(hKey);
    return TRUE;
}
//Write data in registry
BOOL WriteDwordInRegistry(HKEY hKeyParent, PWCHAR subkey, PWCHAR valueName,DWORD data)
{
    DWORD Ret;
    HKEY hKey;
    //Open the key
    Ret = RegOpenKeyEx(
              hKeyParent,
              subkey,
              0,
              KEY_WRITE,
              &hKey
          );
    if (Ret == ERROR_SUCCESS)
    {
        //Set the value in key
        if (ERROR_SUCCESS !=
                RegSetValueEx(
                    hKey,
                    valueName,
                    0,
                    REG_DWORD,
                    reinterpret_cast<BYTE *>(&data),
                    sizeof(data)))
        {
            RegCloseKey(hKey);
            return FALSE;
        }
        //close the key
        RegCloseKey(hKey);
        return TRUE;
    }
    return FALSE;
}
//Read data from registry
BOOL readDwordValueRegistry(HKEY hKeyParent, PWCHAR subkey, PWCHAR valueName, DWORD *readData)
{
    HKEY hKey;
    DWORD Ret;
    //Check if the registry exists
    Ret = RegOpenKeyEx(
              hKeyParent,
              subkey,
              0,
              KEY_READ,
              &hKey
          );
    if (Ret == ERROR_SUCCESS)
    {
        DWORD data;
        DWORD len = sizeof(DWORD);//size of data
        Ret = RegQueryValueEx(
                  hKey,
                  valueName,
                  NULL,
                  NULL,
                  (LPBYTE)(&data),
                  &len
              );
        if (Ret == ERROR_SUCCESS)
        {
            RegCloseKey(hKey);
            (*readData) = data;
            return TRUE;
        }
        RegCloseKey(hKey);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
//Write range and type into the registry
BOOL writeStringInRegistry(HKEY hKeyParent, PWCHAR subkey, PWCHAR valueName, PWCHAR strData)
{
    DWORD Ret;
    HKEY hKey;
    //Check if the registry exists
    Ret = RegOpenKeyEx(
              hKeyParent,
              subkey,
              0,
              KEY_WRITE,
              &hKey
          );
    if (Ret == ERROR_SUCCESS)
    {
        if (ERROR_SUCCESS !=
                RegSetValueEx(
                    hKey,
                    valueName,
                    0,
                    REG_SZ,
                    (LPBYTE)(strData),
                    ((((DWORD)lstrlen(strData) + 1)) * 2)))
        {
            RegCloseKey(hKey);
            return FALSE;
        }
        RegCloseKey(hKey);
        return TRUE;
    }
    return FALSE;
}
//read customer infromation from the registry
BOOL readUserInfoFromRegistry(HKEY hKeyParent, PWCHAR subkey, PWCHAR valueName, PWCHAR *readData)
{
    HKEY hKey;
    DWORD len = TOTAL_BYTES_READ;
    DWORD readDataLen = len;
    PWCHAR readBuffer = (PWCHAR )malloc(sizeof(PWCHAR)* len);
    if (readBuffer == NULL)
        return FALSE;
    //Check if the registry exists
    DWORD Ret = RegOpenKeyEx(
                    hKeyParent,
                    subkey,
                    0,
                    KEY_READ,
                    &hKey
                );
    if (Ret == ERROR_SUCCESS)
    {
        Ret = RegQueryValueEx(
                  hKey,
                  valueName,
                  NULL,
                  NULL,
                  (BYTE*)readBuffer,
                  &readDataLen
              );
        while (Ret == ERROR_MORE_DATA)
        {
            // Get a buffer that is big enough.
            len += OFFSET_BYTES;
            readBuffer = (PWCHAR)realloc(readBuffer, len);
            readDataLen = len;
            Ret = RegQueryValueEx(
                      hKey,
                      valueName,
                      NULL,
                      NULL,
                      (BYTE*)readBuffer,
                      &readDataLen
                  );
        }
        if (Ret != ERROR_SUCCESS)
        {
            RegCloseKey(hKey);
            return false;;
        }
        *readData = readBuffer;
        RegCloseKey(hKey);
        return true;
    }
    else
    {
        return false;
    }
}
#endif

};
