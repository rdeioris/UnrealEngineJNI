// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JNIObject.h"
#include "JNIValue.h"
#include "JNIMethodID.h"
#include "JNIThrowable.h"
#include "JNIClass.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class UNREALENGINEJNI_API UJNIClass : public UJNIObject
{
	GENERATED_BODY()

public:
	jclass GetJClass()
	{
		return (jclass)JNIObject;
	}

};
