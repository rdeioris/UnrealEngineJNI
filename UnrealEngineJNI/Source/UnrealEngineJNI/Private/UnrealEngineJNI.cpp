// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UnrealEngineJNI.h"

#define LOCTEXT_NAMESPACE "FUnrealEngineJNIModule"

DEFINE_LOG_CATEGORY(LogJNI);

void FUnrealEngineJNIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	JavaVirtualMachine = nullptr;
	JavaVirtualMachineMainThread = nullptr;
	JavaVirtualMachineArgs.version = JNI_VERSION_1_6;
	JavaVMOption option0;
	option0.optionString = "-Djava.class.path=D:/JavaTest001/Content";
	JavaVirtualMachineArgs.nOptions = 1;
	JavaVirtualMachineArgs.options = &option0;

	jint JavaRet = JNI_CreateJavaVM(&JavaVirtualMachine, (void **)&JavaVirtualMachineMainThread, &JavaVirtualMachineArgs);
	if (JavaRet != JNI_OK)
	{
		UE_LOG(LogJNI, Error, TEXT("Unable to initialize Java Virtual Machine"));
		return;
	}
	UE_LOG(LogJNI, Log, TEXT("Successfully initialized Java Virtual Machine"));

}

void FUnrealEngineJNIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (JavaVirtualMachine)
	{
		// NOTE: I currently leave it empty as destroying a JVM is really flaky on any implementation i tried
	}
}

bool FUnrealEngineJNIModule::RegisterJNINative(const char *ClassName, const char *MethodName, const char *Signature, void *Function)
{
	JNIEnv *Env = JavaVirtualMachineMainThread;
	if (!Env)
	{
		UE_LOG(LogJNI, Error, TEXT("The Java Virtual Machine is not initialized"));
		return false;
	}
	jclass JClass = Env->FindClass(ClassName);
	if (Env->ExceptionCheck())
	{
		UE_LOG(LogJNI, Error, TEXT("Unable to find Java Class %s"), UTF8_TO_TCHAR(ClassName));
		Env->ExceptionClear();
		return false;
	}
	JNINativeMethod JNativeMethod;
	JNativeMethod.name = (char*)MethodName;
	JNativeMethod.signature = (char *)Signature;
	JNativeMethod.fnPtr = Function;
	if (Env->RegisterNatives(JClass, &JNativeMethod, 1) != JNI_OK)
	{
		UE_LOG(LogJNI, Error, TEXT("Unable to register Java Native Method %s for Java Class %s"), UTF8_TO_TCHAR(MethodName), UTF8_TO_TCHAR(ClassName));
		return false;
	}

	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealEngineJNIModule, UnrealEngineJNI)