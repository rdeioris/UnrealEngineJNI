// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UnrealEngineJNIMessaging.h"

#define LOCTEXT_NAMESPACE "FUnrealEngineJNIMessagingModule"

void FUnrealEngineJNIMessagingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUnrealEngineJNIMessagingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

bool FUnrealEngineJNIMessagingModule::JNIEnqueue(FString Queue, FString Message)
{
	FScopeLock Lock(&JNIMessagingLock);

	JNIMessagingQueues[Queue].Enqueue(Message);

	return true;
}

bool FUnrealEngineJNIMessagingModule::JNIDequeue(FString Queue, FString &Message)
{
	FScopeLock Lock(&JNIMessagingLock);

	return JNIMessagingQueues[Queue].Dequeue(Message);

}

bool FUnrealEngineJNIMessagingModule::JNIIsEmpty(FString Queue)
{
	FScopeLock Lock(&JNIMessagingLock);

	return JNIMessagingQueues[Queue].IsEmpty();

}

bool FUnrealEngineJNIMessagingModule::JNIPeek(FString Queue, FString &Message)
{
	FScopeLock Lock(&JNIMessagingLock);

	return JNIMessagingQueues[Queue].Peek(Message);

}

void FUnrealEngineJNIMessagingModule::JNIEmpty(FString Queue)
{
	FScopeLock Lock(&JNIMessagingLock);

	JNIMessagingQueues[Queue].Empty();

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealEngineJNIMessagingModule, UnrealEngineJNIMessaging)