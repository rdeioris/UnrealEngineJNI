// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIThread.h"

FJNIRunnable::FJNIRunnable(jobject JObject, jmethodID JMethodID)
{
	JNIObject = JObject;
	JNIClass = nullptr;
	JNIMethodID = JMethodID;

	Thread = FRunnableThread::Create(this, TEXT("JNIThread"), 0, TPri_BelowNormal);
	if (!Thread)
	{
		UE_LOG(LogJNI, Error, TEXT("Unable to create new FRunnableThread"));
	}
}

FJNIRunnable::FJNIRunnable(jclass JClass, jmethodID JMethodID)
{
	JNIObject = nullptr;
	JNIClass = JClass;
	JNIMethodID = JMethodID;

	Thread = FRunnableThread::Create(this, TEXT("JNIThread"), 0, TPri_BelowNormal);
	if (!Thread)
	{
		UE_LOG(LogJNI, Error, TEXT("Unable to create new FRunnableThread"));
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

	JThreadClass = AttachedJNIEnv->FindClass("java/lang/Thread");
	if (AttachedJNIEnv->ExceptionCheck())
	{
		AttachedJNIEnv->ExceptionClear();
		UE_LOG(LogJNI, Error, TEXT("unable to get java/lang/Thread class"));
		Vm->DetachCurrentThread();
		return false;
	}

	jmethodID JCurrentThreadMethodID = AttachedJNIEnv->GetStaticMethodID(JThreadClass, "currentThread", "()Ljava/lang/Thread;");
	if (AttachedJNIEnv->ExceptionCheck())
	{
		AttachedJNIEnv->ExceptionClear();
		UE_LOG(LogJNI, Error, TEXT("unable to find currentThread() in java/lang/Thread class"));
		Vm->DetachCurrentThread();
		return false;
	}

	JCurrentThread = AttachedJNIEnv->CallStaticObjectMethod(JThreadClass, JCurrentThreadMethodID);
	if (AttachedJNIEnv->ExceptionCheck())
	{
		AttachedJNIEnv->ExceptionClear();
		UE_LOG(LogJNI, Error, TEXT("unable to get current java/lang/Thread object"));
		Vm->DetachCurrentThread();
		return false;
	}

	JThreadInterrupt = AttachedJNIEnv->GetMethodID(JThreadClass, "interrupt", "()V");
	if (AttachedJNIEnv->ExceptionCheck())
	{
		AttachedJNIEnv->ExceptionClear();
		UE_LOG(LogJNI, Error, TEXT("unable to find interrupt() in java/lang/Thread class"));
		Vm->DetachCurrentThread();
		return false;
	}

	return true;
}

void FJNIRunnable::Stop()
{
	if (Thread)
	{
		// here we are in the main thread
		FUnrealEngineJNIModule &Module = FModuleManager::GetModuleChecked<FUnrealEngineJNIModule>("UnrealEngineJNI");
		JNIEnv *Env = Module.GetJavaVirtualMachineMainThread();
		if (!Env)
		{
			UE_LOG(LogJNI, Error, TEXT("Java Virtual Machine is not initialized"));
			return;
		}

		Env->CallVoidMethod(JCurrentThread, JThreadInterrupt);
		if (Env->ExceptionCheck())
		{
			Env->ExceptionClear();
			UE_LOG(LogJNI, Error, TEXT("unable to send interrupt() to java/lang/Thread"));
			return;
		}

		Thread->WaitForCompletion();
	}

}

uint32 FJNIRunnable::Run()
{
	if (!Vm || !AttachedJNIEnv)
		return 0;

	if (JNIObject && JNIMethodID)
	{
		AttachedJNIEnv->CallVoidMethodA(JNIObject, JNIMethodID, nullptr);
		if (AttachedJNIEnv->ExceptionCheck())
		{
			// TODO report Exception in logs
			AttachedJNIEnv->ExceptionClear();
		}
	}
	else if (JNIClass && JNIMethodID)
	{
		AttachedJNIEnv->CallStaticVoidMethodA(JNIClass, JNIMethodID, nullptr);
		if (AttachedJNIEnv->ExceptionCheck())
		{
			// TODO report Exception in logs
			AttachedJNIEnv->ExceptionClear();
		}
	}


	Vm->DetachCurrentThread();

	return 0;
}

void UJNIThread::StartJNIThread(jobject JObject, jmethodID JMethodID)
{
	JNIRunnable = new FJNIRunnable(JObject, JMethodID);
}

void UJNIThread::StartJNIThread(jclass JClass, jmethodID JMethodID)
{
	JNIRunnable = new FJNIRunnable(JClass, JMethodID);
}

UJNIThread::~UJNIThread()
{
	if (JNIRunnable)
	{
		JNIRunnable->Stop();
		delete(JNIRunnable);
	}
	UE_LOG(LogJNI, Log, TEXT("JNIThread (%p) destroyed"), this);
}
