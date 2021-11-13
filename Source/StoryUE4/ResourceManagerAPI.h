// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ResourceManagerAPI.generated.h"

/**
 * 
 */
UCLASS()
class STORYUE4_API UResourceManagerAPI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "ResourceManager")
	static UTexture2D* LoadTexture(FString fullPath);

	UFUNCTION(BlueprintCallable, Category = "ResourceManager")
	static UTexture2D* LoadContentTexture(FString fullPath);
	
};
