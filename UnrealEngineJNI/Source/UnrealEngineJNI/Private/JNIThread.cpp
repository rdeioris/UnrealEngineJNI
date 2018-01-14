// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIThread.h"

FJNIRunnable::FJNIRunnable()
{
	Thread = FRunnableThread::Create(this, TEXT("JNIThread"), 0, TPri_BelowNormal);
	if (!Thread)
	{
		UE_LOG(LogJNI, Error, TEXT("Junable to create new FRunnableThread"));
	}
}

bool FJNIRunnable::Init()
{
	FUnrealEngineJNIModule &Module = FModuleManager::GetModuleChecked<FUnrealEngineJNIModule>("UnrealEngineJNI");
	Vm = Module.GetJavaVirtualMachine();
	if (!Vm)
	{
		UE_LOG(LogJNI, Error, TEXT("Java Virtual Machine is not initialized"));
		return false;
	}
	AttachedJNIEnv = nullptr;

	if (Vm->AttachCurrentThread((void **)&AttachedJNIEnv, nullptr) != JNI_OK)
	{
		UE_LOG(LogJNI, Error, TEXT("unable to attach thread to Java Virtual Machine"));
		return false;
	}

	return true;
}

void FJNIRunnable::Stop()
{
	UE_LOG(LogJNI, Error, TEXT("Calling STOP"));
	if (Thread)
	{
		Thread->WaitForCompletion();
	}

}

uint32 FJNIRunnable::Run()
{
	int32 Counter = 0;
	for (;;)
	{
		FPlatformProcess::Sleep(1);
		UE_LOG(LogJNI, Warning, TEXT("Counter = %d"), Counter++);
		if (Counter > 10)
			break;
	}


	if (Vm && AttachedJNIEnv)
	{
		Vm->DetachCurrentThread();
	}

	return 0;
}

void UJNIThread::StartJNIThread()
{
	JNIRunnable = new FJNIRunnable();
}

UJNIThread::~UJNIThread()
{
	if (JNIRunnable)
	{
		JNIRunnable->Stop();
		delete(JNIRunnable);
	}
	UE_LOG(LogJNI, Error, TEXT("JNIThread destroyed"));
}
