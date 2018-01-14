// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealEngineJNI.h"
#include "JNIEnvCheck.h"
#include "JNIMethodID.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALENGINEJNI_API UJNIMethodID : public UObject, public FJNIEnvCheck
{
	GENERATED_BODY()
	
public:
	UJNIMethodID();
	void SetJMethodID(JNIEnv *Env, jmethodID JMethodID);

	jmethodID GetJMethodID()
	{
		return JNIMethodID;
	}
	
protected:
	jmethodID JNIMethodID;
	JNIEnv *OwningEnv;
};
