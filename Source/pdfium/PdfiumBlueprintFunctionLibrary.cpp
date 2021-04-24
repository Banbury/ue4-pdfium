// Fill out your copyright notice in the Description page of Project Settings.

#include "PdfiumBlueprintFunctionLibrary.h"

UTexture2D* UPdfiumBlueprintFunctionLibrary::RenderPage(FPdfDocument document, int page)
{
	int size = 2048;
	UTexture2D*	texture = UTexture2D::CreateTransient(size, size);
	texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	texture->SRGB = 0;
	FTexture2DMipMap& Mip = texture->PlatformData->Mips[0];
	void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);

	FPDF_BITMAP bm = FPDFBitmap_Create(size, size, 0);
	if (bm != NULL) {
		FPDF_DOCUMENT doc =  document.doc;
		FPDF_PAGE pdfPage = FPDF_LoadPage(doc, page);

		void* buf = FPDFBitmap_GetBuffer(bm);
		int stride = FPDFBitmap_GetStride(bm);
		int w = FPDFBitmap_GetWidth(bm);
		int h = FPDFBitmap_GetHeight(bm);

		FPDFBitmap_FillRect(bm, 0, 0, size-1, size-1, 0xffffffff);
		FPDF_RenderPageBitmap(bm, pdfPage, 0, 0, size-1, size-1, 0, 0);
		FPDF_ClosePage(pdfPage);

		FMemory::Memcpy(Data, buf, stride * h);

		FPDFBitmap_Destroy(bm);
	}

	Mip.BulkData.Unlock();
	texture->UpdateResource();
	return texture;
}

FPdfDocument UPdfiumBlueprintFunctionLibrary::LoadDocument(FString filename)
{
	FPdfDocument doc = FPdfDocument();
	doc.doc = FPDF_LoadDocument(TCHAR_TO_ANSI(*filename), NULL);
	return doc;
}

void UPdfiumBlueprintFunctionLibrary::CloseDocument(FPdfDocument document)
{
	FPDF_CloseDocument(document.doc);
}

int UPdfiumBlueprintFunctionLibrary::GetLastError()
{
	return FPDF_GetLastError();
}

int UPdfiumBlueprintFunctionLibrary::GetPermissions(FPdfDocument document)
{
	return FPDF_GetDocPermissions(document.doc);
}

void UPdfiumBlueprintFunctionLibrary::GetPageSize(FPdfDocument document, int page, float & width, float & height)
{
	FS_SIZEF size;
	FPDF_GetPageSizeByIndexF(document.doc, page, &size);
	width = size.width;
	height = size.height;
}

int UPdfiumBlueprintFunctionLibrary::GetPageCount(FPdfDocument document)
{
	return FPDF_GetPageCount(document.doc);
}
