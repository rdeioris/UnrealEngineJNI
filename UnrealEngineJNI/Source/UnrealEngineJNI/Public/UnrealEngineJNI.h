// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Paths.h"
#include "HAL/IConsoleManager.h"
#include <jni.h>


UNREALENGINEJNI_API DECLARE_LOG_CATEGORY_EXTERN(LogJNI, Log, All);



class UNREALENGINEJNI_API FUnrealEngineJNIModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	JavaVM *GetJavaVirtualMachine()
	{
		return JavaVirtualMachine;
	}

	JNIEnv *GetJavaVirtualMachineMainThread()
	{
		return JavaVirtualMachineMainThread;
	}

	bool RegisterJNINative(const char *ClassName, const char *MethodName, const char *Signature, void *Function);

private:
	JavaVM *JavaVirtualMachine;
	JavaVMInitArgs JavaVirtualMachineArgs;
	JNIEnv *JavaVirtualMachineMainThread;


	void ConsoleJNICallStaticStringMethod(const TArray<FString> &Args);
};