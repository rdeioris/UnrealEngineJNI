// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UnrealEngineJNILogging.h"

#define LOCTEXT_NAMESPACE "FUnrealEngineJNILoggingModule"

static void Java_com_unrealengine_Logging_log(JNIEnv *Env, jclass JClass, jstring JString)
{
	const char *Message = Env->GetStringUTFChars(JString, nullptr);
	if (!Message)
		return;
	UE_LOG(LogJNI, Log, TEXT("%s"), UTF8_TO_TCHAR(Message));
	Env->ReleaseStringUTFChars(JString, Message);
}

static void Java_com_unrealengine_Logging_logWarning(JNIEnv *Env, jclass JClass, jstring JString)
{
	const char *Message = Env->GetStringUTFChars(JString, nullptr);
	if (!Message)
		return;
	UE_LOG(LogJNI, Warning, TEXT("%s"), UTF8_TO_TCHAR(Message));
	Env->ReleaseStringUTFChars(JString, Message);
}

static void Java_com_unrealengine_Logging_logError(JNIEnv *Env, jclass JClass, jstring JString)
{
	const char *Message = Env->GetStringUTFChars(JString, nullptr);
	if (!Message)
		return;
	UE_LOG(LogJNI, Error, TEXT("%s"), UTF8_TO_TCHAR(Message));
	Env->ReleaseStringUTFChars(JString, Message);
}

void FUnrealEngineJNILoggingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FUnrealEngineJNIModule &Module = FModuleManager::GetModuleChecked<FUnrealEngineJNIModule>("UnrealEngineJNI");
	Module.RegisterJNINative("com/unrealengine/Logging", "log", "(Ljava/lang/String;)V", Java_com_unrealengine_Logging_log);
	Module.RegisterJNINative("com/unrealengine/Logging", "logWarning", "(Ljava/lang/String;)V", Java_com_unrealengine_Logging_logWarning);
	Module.RegisterJNINative("com/unrealengine/Logging", "logError", "(Ljava/lang/String;)V", Java_com_unrealengine_Logging_logError);
}

void FUnrealEngineJNILoggingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealEngineJNILoggingModule, UnrealEngineJNILogging)