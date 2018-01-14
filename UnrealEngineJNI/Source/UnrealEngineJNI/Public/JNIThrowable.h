// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JNIObject.h"
#include "JNIEnvCheck.h"
#include "JNIThrowable.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALENGINEJNI_API UJNIThrowable : public UJNIObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetJNIExceptionMessage();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetJNIExceptionClassName();
	
	
};
