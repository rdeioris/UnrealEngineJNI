// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JNIObject.h"
#include "JNIValue.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UNREALENGINEJNI_API FJNIValue
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool JBoolean;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JFloat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UJNIObject *JObject;

	UPROPERTY(EditAnywhere)
	int64 JLong;
};
