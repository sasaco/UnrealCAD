// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

#include "Engine.h"
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"


void UMyBlueprintFunctionLibrary::OpenPDFDialog(const FString& DefaultPath, EOpenPDFDialogResult& OutputPin, FString& FileName)
{
	TArray<FString> FileNameTemp;
	OutputPin = ExecOpenFileDialog(DefaultPath, FileNameTemp, false);
	if (OutputPin == EOpenPDFDialogResult::Successful)
	{
		FileName = FileNameTemp[0];
	}
}

EOpenPDFDialogResult UMyBlueprintFunctionLibrary::ExecOpenFileDialog(const FString& DefaultPath, TArray<FString>& FileNames, bool bIsMultiple)
{
	void* WindowHandle = GetWindowHandle();
	if (WindowHandle)
	{
		IDesktopPlatform* desktopPlatform = FDesktopPlatformModule::Get();
		if (desktopPlatform)
		{
			bool result = desktopPlatform->OpenFileDialog(
				GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle(),
				TEXT("Open PDF Dialog"),
				DefaultPath,
				TEXT(""),
				TEXT("PDF File (.pdf)|*.pdf"),
				(bIsMultiple ? EFileDialogFlags::Type::Multiple : EFileDialogFlags::Type::None),
				FileNames
			);

			if (result)
			{
				// 相対パスを絶対パスに変換
				for (FString& fileName : FileNames)
				{
					fileName = FPaths::ConvertRelativePathToFull(fileName);
					//UE_LOG(PDFImporter, Log, TEXT("Open PDF Dialog : %s"), *fileName);
				}
				return EOpenPDFDialogResult::Successful;
			}
		}
	}
	//UE_LOG(PDFImporter, Log, TEXT("Open PDF Dialog : Cancelled"));
	return EOpenPDFDialogResult::Cancelled;
}

void* UMyBlueprintFunctionLibrary::GetWindowHandle()
{
	// エディタの場合
	if (GIsEditor)
	{
		IMainFrameModule& MainFrameModule = IMainFrameModule::Get();
		TSharedPtr<SWindow> MainWindow = MainFrameModule.GetParentWindow();

		if (MainWindow.IsValid() && MainWindow->GetNativeWindow().IsValid())
		{
			return MainWindow->GetNativeWindow()->GetOSWindowHandle();
		}
	}
	// 実行時の場合
	else
	{
		if (GEngine && GEngine->GameViewport)
		{
			return GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
		}
	}

	return nullptr;
}