// Fill out your copyright notice in the Description page of Project Settings.


#include "BatchProcessingTexture.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/LocalTimestampDirectoryVisitor.h"
#include "UObject/ConstructorHelpers.h"

const FString Extensions = TEXT("uasset");
const FString FilterString = TEXT(".");
const FString Prefix = TEXT("Texture2D'/Game/");
const FString Prefix_PKG = TEXT("/Game/");
#define print(text) GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::White,text);


FReply UBatchProcessingTexture::ClickedButton()
{

    IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
    TArray<FString> Files;
    TArray<FString> Names;
    FString path = FPaths::Combine(FPaths::ProjectContentDir(),TEXT("beffio/Medieval_Kingdom/Content/Textures"));
    //FileManager.FindFiles(Files,*path,*Extensions);


    TArray<FString> directoriesToSkip;
    FLocalTimestampDirectoryVisitor Visitor(FileManager, directoriesToSkip, directoriesToSkip, false);    
    FileManager.IterateDirectory(*path, Visitor);
   
 
    for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
    {
        FString filePath = TimestampIt.Key();        
        FString fileName = FPaths::GetCleanFilename(filePath);
        
        FString Left;
        FString Right;
        fileName.Split(FilterString,&Left,&Right);
        fileName = Left;
        if(filePath.Len() > FPaths::ProjectContentDir().Len())
            filePath = filePath.Right(filePath.Len() - FPaths::ProjectContentDir().Len());
        else
            print(TEXT("filePath.Len() < FPaths::ProjectContentDir().Len()"))
        FString Left_m;
        FString Right_m;
        filePath.Split(FilterString,&Left_m,&Right_m);
        filePath = Left_m;
        Names.Add(fileName);
        bool shouldAddFile = true;
        Files.Add(filePath);
        
    }

    FString ss = TEXT("Texture2D'/Game/beffio/Medieval_Kingdom/Content/Textures/Anvil/T_Anvil_AO.T_Anvil_AO'");
   
    for (int32 i= 0; i< Files.Num()-1 ;++i)
    {
        FString LoadPath =Prefix + Files[i]+ TEXT(".") +Names[i] + TEXT("'");
       
        FString Left;
        FString Right;
        //UPackage::Save()
        //UPackage::SavePackage()
        //UPackage* PKG =FindPackage(nullptr,*LoadPath);
        
        auto* Texture = LoadObject<UTexture>(nullptr,*LoadPath);
        if (Texture)
        {
            Texture->LODBias=2;
            auto c =Texture->GetClass()->GetDefaultObject(true);
            auto d=  Cast<UTexture>(c);
            d->LODBias=2;
            Texture->MarkPackageDirty();
            FString PKGPath = Prefix_PKG + Files[i] ;
            UPackage* PKG = FindPackage(nullptr,*PKGPath);
            if(PKG)
            {
                PKG->MarkPackageDirty();
                FString PKGFileName; 
                FPackageName::TryConvertLongPackageNameToFilename(PKGPath,PKGFileName, FPackageName::GetAssetPackageExtension());
                UPackage::Save(PKG,Texture,EObjectFlags::RF_Public|EObjectFlags::RF_DefaultSubObject,*PKGFileName, GError, nullptr, true, true, SAVE_NoError);
                //PKG->Save(nullptr,Texture,EObjectFlags::RF_Public|EObjectFlags::RF_Standalone,*PKGFileName, GError, nullptr, true, true, SAVE_NoError);
                print(TEXT("SUCCESS"));
            }
            else
            {
                print(PKGPath);
            }
        }  
    }

    if (Files.Num() == 0)
    {
        print(path +Extensions + TEXT("Find Nothing"));
    }
    
   
    
    return FReply::Handled();
}
