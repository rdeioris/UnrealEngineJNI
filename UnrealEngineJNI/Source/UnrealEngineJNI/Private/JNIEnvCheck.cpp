// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIEnvCheck.h"

JNIEnv *FJNIEnvCheck::GetJNIEnv(JNIEnv *EnvToCompare) const
{
	FUnrealEngineJNIModule &Module = FModuleManager::GetModuleChecked<FUnrealEngineJNIModule>("UnrealEngineJNI");
	JavaVM *Vm = Module.GetJavaVirtualMachine();
	if (!Vm)
	{
		UE_LOG(LogJNI, Error, TEXT("Java Virtual Machine is not initialized"));
		return nullptr;
	}
	JNIEnv *CurrentJEnv = nullptr;
	if (Vm->GetEnv((void **)&CurrentJEnv, JNI_VERSION_1_6) != JNI_OK)
	{
		UE_LOG(LogJNI, Error, TEXT("The current thread is not attached to the Java Virtual Machine"));
		return nullptr;
	}

	if (EnvToCompare && EnvToCompare != CurrentJEnv)
	{
		UE_LOG(LogJNI, Error, TEXT("The current thread does not match the specified one"));
		return nullptr;
	}

	return CurrentJEnv;
}
