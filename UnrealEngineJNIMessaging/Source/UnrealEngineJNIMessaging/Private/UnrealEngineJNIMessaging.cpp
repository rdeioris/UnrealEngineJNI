// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UnrealEngineJNIMessaging.h"

#define LOCTEXT_NAMESPACE "FUnrealEngineJNIMessagingModule"

static jboolean Java_com_unrealengine_Messaging_enqueue(JNIEnv *Env, jclass JClass, jstring Queue, jstring Message)
{
	const char *StrQueue = Env->GetStringUTFChars(Queue, nullptr);
	if (!StrQueue)
		return JNI_FALSE;

	const char *StrMessage = Env->GetStringUTFChars(Message, nullptr);
	if (!StrMessage)
	{
		Env->ReleaseStringUTFChars(Queue, StrQueue);
		return JNI_FALSE;
	}

	FUnrealEngineJNIMessagingModule &Module = FModuleManager::GetModuleChecked<FUnrealEngineJNIMessagingModule>("UnrealEngineJNIMessaging");
	bool bSuccess = Module.JNIEnqueue(FString(StrQueue), FString(StrMessage));
	
	Env->ReleaseStringUTFChars(Queue, StrQueue);
	Env->ReleaseStringUTFChars(Message, StrMessage);


	return bSuccess ? JNI_TRUE : JNI_FALSE;
}

void FUnrealEngineJNIMessagingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FUnrealEngineJNIModule &Module = FModuleManager::GetModuleChecked<FUnrealEngineJNIModule>("UnrealEngineJNI");
	Module.RegisterJNINative("com/unrealengine/Messaging", "enqueue", "(Ljava/lang/String;Ljava/lang/String;)Z", Java_com_unrealengine_Messaging_enqueue);
}

void FUnrealEngineJNIMessagingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

bool FUnrealEngineJNIMessagingModule::JNIEnqueue(FString Queue, FString Message)
{
	FScopeLock Lock(&JNIMessagingLock);

	if (!JNIMessagingQueues.Contains(Queue))
	{
		TSharedPtr<TQueue<FString, EQueueMode::Mpsc>> NewQueue(new TQueue<FString, EQueueMode::Mpsc>());
		JNIMessagingQueues.Add(Queue, NewQueue);
	}

	JNIMessagingQueues[Queue]->Enqueue(Message);

	return true;
}

bool FUnrealEngineJNIMessagingModule::JNIDequeue(FString Queue, FString &Message)
{
	FScopeLock Lock(&JNIMessagingLock);

	if (!JNIMessagingQueues.Contains(Queue))
	{
		return false;
	}

	return JNIMessagingQueues[Queue]->Dequeue(Message);

}

bool FUnrealEngineJNIMessagingModule::JNIIsEmpty(FString Queue)
{
	FScopeLock Lock(&JNIMessagingLock);

	if (!JNIMessagingQueues.Contains(Queue))
	{
		return true;
	}

	return JNIMessagingQueues[Queue]->IsEmpty();

}

bool FUnrealEngineJNIMessagingModule::JNIPeek(FString Queue, FString &Message)
{
	FScopeLock Lock(&JNIMessagingLock);

	if (!JNIMessagingQueues.Contains(Queue))
	{
		return false;
	}

	return JNIMessagingQueues[Queue]->Peek(Message);

}

void FUnrealEngineJNIMessagingModule::JNIEmpty(FString Queue)
{
	FScopeLock Lock(&JNIMessagingLock);

	if (!JNIMessagingQueues.Contains(Queue))
	{
		return;
	}

	JNIMessagingQueues[Queue]->Empty();

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealEngineJNIMessagingModule, UnrealEngineJNIMessaging)