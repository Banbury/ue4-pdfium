// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define __WINDOWS__
#include <WindowsHWrapper.h>
#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "fpdfview.h"
#include "PdfiumBlueprintFunctionLibrary.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FPdfDocument
{
	GENERATED_USTRUCT_BODY()

	FPDF_DOCUMENT doc;
};


/**
 * 
 */
UCLASS()
class PDFIUM_API UPdfiumBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Pdfium")
	static UTexture2D* RenderPage(FPdfDocument document, int page);

	UFUNCTION(BlueprintCallable, Category = "Pdfium")
	static FPdfDocument LoadDocument(FString filename);

	UFUNCTION(BlueprintCallable, Category = "Pdfium")
	static void CloseDocument(FPdfDocument document);

	UFUNCTION(BlueprintCallable, Category = "Pdfium")
	static int GetPageCount(FPdfDocument document);

	UFUNCTION(BlueprintCallable, Category = "Pdfium")
	static int GetLastError();

	UFUNCTION(BlueprintCallable, Category = "Pdfium")
	static int GetPermissions(FPdfDocument document);

	UFUNCTION(BlueprintCallable, Category = "Pdfium")
	static void GetPageSize(FPdfDocument document, int page, float &width, float &height);
};
