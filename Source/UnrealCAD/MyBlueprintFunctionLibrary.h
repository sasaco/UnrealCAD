// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */

UENUM()
enum class EOpenPDFDialogResult : uint8
{
	Successful, Cancelled
};



UCLASS()
class UNREALCAD_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Get the file path of the selected PDF file
	UFUNCTION(BlueprintCallable, Category = "PDFImporter | OpenFileDialog", meta = (AdvancedDisplay = "DefaultPath", DisplayName = "Open PDF Dialog", ExpandEnumAsExecs = "OutputPin"))
		static void OpenPDFDialog(const FString& DefaultPath, EOpenPDFDialogResult& OutputPin, FString& FileName);


private:
	// Get window handle
	static void* GetWindowHandle();

	// Run open file dialog
	static EOpenPDFDialogResult ExecOpenFileDialog(const FString& DefaultPath, TArray<FString>& FileNames, bool bIsMultiple);
};

