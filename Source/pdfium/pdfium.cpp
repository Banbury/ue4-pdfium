// Fill out your copyright notice in the Description page of Project Settings.

#include "pdfium.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FPdfiumModule, pdfium, "pdfium" );

void FPdfiumModule::StartupModule()
{
	FPDF_InitLibrary();
}

void FPdfiumModule::ShutdownModule()
{
	FPDF_DestroyLibrary();
}
