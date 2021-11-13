// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceManagerAPI.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "UObject/UObjectGlobals.h"

//从Content里面加载一个UTexture2D资源
UTexture2D* UResourceManagerAPI::LoadContentTexture(FString fullPath)
{
	UTexture2D* MyTexture = NULL;
	FText myfile = FText::FromString(fullPath);
	const TCHAR* mystr = *fullPath;
	MyTexture = LoadObject<UTexture2D>(NULL, mystr, NULL, LOAD_None, NULL);
	return MyTexture;
}

//从本地加载一个图像文件
UTexture2D* UResourceManagerAPI::LoadTexture(FString fullPath)
{
	if (!FPaths::FileExists(fullPath)) {
		return NULL;
	}

	TArray<uint8> RawFileData;
	UTexture2D* MyTexture = NULL;
	if (!FFileHelper::LoadFileToArray(RawFileData, *fullPath)) {
		return NULL;
	}

	IImageWrapperModule& ImageWrapperMoudule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

	EImageFormat format = EImageFormat::Invalid;
	if (fullPath.EndsWith(TEXT(".png")))
	{
		format = EImageFormat::PNG;
	}
	else if (fullPath.EndsWith(TEXT(".jpg")) || fullPath.EndsWith(TEXT(".jpeg")))
	{
		format = EImageFormat::JPEG;
	}
	else if (fullPath.EndsWith(TEXT(".bmp")))
	{
		format = EImageFormat::BMP;
	}

	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperMoudule.CreateImageWrapper(format);
	if (!ImageWrapper.IsValid()) {
		return NULL;
	}
	if (!ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num())) {
		return NULL;
	}
	TArray<uint8> UncompressedBGRA;
	if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA)) {
		return NULL;
	}

	// Create the UTexture for rendering
	UTexture2D* result = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

	// Fill in the source data from the file
	void* TextureData = result->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
	result->PlatformData->Mips[0].BulkData.Unlock();

	// Update the rendering resource from data.
	result->UpdateResource();
	
	return result;
}