// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "UnrealEngineJNI.h"
#include "JNIThread.generated.h"


class FJNIRunnable : public FRunnable
{
private:
	JNIEnv *AttachedJNIEnv;
	JavaVM *Vm;
	FRunnableThread* Thread;

public:
	FJNIRunnable();
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
};

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALENGINEJNI_API UJNIThread : public UObject
{
	GENERATED_BODY()
	
private:
	FJNIRunnable *JNIRunnable;
	
public:
	void StartJNIThread();
	~UJNIThread();
};
