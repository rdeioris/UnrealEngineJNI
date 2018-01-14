// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealEngineJNI.h"
#include "JNIEnvCheck.h"
#include "JNIFieldID.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class UNREALENGINEJNI_API UJNIFieldID : public UObject, public FJNIEnvCheck
{
	GENERATED_BODY()

public:
	UJNIFieldID();
	void SetJFieldID(JNIEnv *Env, jfieldID JFieldID);

	jfieldID GetJFieldID()
	{
		return JNIFieldID;
	}

protected:
	jfieldID JNIFieldID;
	JNIEnv *OwningEnv;


};
