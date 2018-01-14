// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealEngineJNI.h"
#include "JNIEnvCheck.h"
#include "JNIObject.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class UNREALENGINEJNI_API UJNIObject : public UObject, public FJNIEnvCheck
{
	GENERATED_BODY()

public:
	UJNIObject();
	~UJNIObject();
	void SetJObject(JNIEnv *Env, jobject JObject);

	jobject GetJObject()
	{
		return JNIObject;
	}


protected:
	jobject JNIObjectReference;
	jobject JNIObject;
	JNIEnv *OwningEnv;

	bool CheckJNIExceptionAndClear();

};
