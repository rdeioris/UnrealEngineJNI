// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealEngineJNI.h"

/**
 * 
 */
class UNREALENGINEJNI_API FJNIEnvCheck
{
public:
	JNIEnv *GetJNIEnv(JNIEnv *EnvToCompare) const;
};
