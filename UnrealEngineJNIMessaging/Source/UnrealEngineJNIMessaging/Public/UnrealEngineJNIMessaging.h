// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Queue.h"
#include "ScopeLock.h"

class FUnrealEngineJNIMessagingModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	bool JNIEnqueue(FString Queue, FString Message);
	bool JNIDequeue(FString Queue, FString &Message);
	bool JNIIsEmpty(FString Queue);
	bool JNIPeek(FString Queue, FString &Message);
	void JNIEmpty(FString Queue);

private:
	FCriticalSection JNIMessagingLock;
	TMap<FString, TQueue<FString, EQueueMode::Mpsc>> JNIMessagingQueues;
};