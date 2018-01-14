// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIComponent.h"

JNIEnv *UJNIComponent::GetJavaVirtualMachineMainThread()
{
	FUnrealEngineJNIModule &Module = FModuleManager::GetModuleChecked<FUnrealEngineJNIModule>("UnrealEngineJNI");
	JNIEnv *Env = Module.GetJavaVirtualMachineMainThread();
	if (!Env)
	{
		UE_LOG(LogJNI, Error, TEXT("Java Virtual Machine is not initialized"));
		return nullptr;
	}
	return Env;
}

bool UJNIComponent::CheckJNIException(JNIEnv *Env, UJNIThrowable *&Exception)
{
	if (Env->ExceptionCheck())
	{
		jthrowable JThrowable = Env->ExceptionOccurred();
		UJNIThrowable *JNIThrowable = NewObject<UJNIThrowable>();
		JNIThrowable->SetJObject(Env, JThrowable);
		Env->ExceptionClear();
		Exception = JNIThrowable;
		FString ClassName = JNIThrowable->GetJNIExceptionClassName();
		FString Message = JNIThrowable->GetJNIExceptionMessage();
		if (OnJNIException.IsBound())
			OnJNIException.Broadcast(ClassName, Message);
		return false;
	}
	return true;
}

// Sets default values for this component's properties
UJNIComponent::UJNIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UJNIComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UJNIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UJNIClass *UJNIComponent::JNIFindClass(FString ClassName, bool & bSuccess, UJNIThrowable *& Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env)
	{
		return nullptr;
	}
	jclass JClass = Env->FindClass(TCHAR_TO_UTF8(*ClassName));
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return nullptr;

	UJNIClass *JNIClass = NewObject<UJNIClass>();
	JNIClass->SetJObject(Env, JClass);
	return JNIClass;
}

UJNIMethodID *UJNIComponent::JNIGetMethodID(UJNIClass *JNIClass, FString MethodName, FString Signature, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIClass)
	{
		return nullptr;
	}
	jmethodID JMethodID = Env->GetMethodID(JNIClass->GetJClass(), TCHAR_TO_UTF8(*MethodName), TCHAR_TO_UTF8(*Signature));
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return nullptr;

	UJNIMethodID *JNIMethodID = NewObject<UJNIMethodID>();
	JNIMethodID->SetJMethodID(Env, JMethodID);
	return JNIMethodID;
}

UJNIFieldID *UJNIComponent::JNIGetFieldID(UJNIClass *JNIClass, FString FieldName, FString Signature, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIClass)
	{
		return nullptr;
	}
	jfieldID JFieldID = Env->GetFieldID(JNIClass->GetJClass(), TCHAR_TO_UTF8(*FieldName), TCHAR_TO_UTF8(*Signature));
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return nullptr;

	UJNIFieldID *JNIFieldID = NewObject<UJNIFieldID>();
	JNIFieldID->SetJFieldID(Env, JFieldID);
	return JNIFieldID;
}

UJNIFieldID *UJNIComponent::JNIGetStaticFieldID(UJNIClass *JNIClass, FString FieldName, FString Signature, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIClass)
	{
		return nullptr;
	}
	jfieldID JFieldID = Env->GetStaticFieldID(JNIClass->GetJClass(), TCHAR_TO_UTF8(*FieldName), TCHAR_TO_UTF8(*Signature));
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return nullptr;

	UJNIFieldID *JNIFieldID = NewObject<UJNIFieldID>();
	JNIFieldID->SetJFieldID(Env, JFieldID);
	return JNIFieldID;
}



UJNIMethodID *UJNIComponent::JNIGetStaticMethodID(UJNIClass *JNIClass, FString MethodName, FString Signature, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIClass)
	{
		return nullptr;
	}
	jmethodID JMethodID = Env->GetStaticMethodID(JNIClass->GetJClass(), TCHAR_TO_UTF8(*MethodName), TCHAR_TO_UTF8(*Signature));
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return nullptr;

	UJNIMethodID *JNIMethodID = NewObject<UJNIMethodID>();
	JNIMethodID->SetJMethodID(Env, JMethodID);
	return JNIMethodID;
}

UJNIObject *UJNIComponent::JNICallStaticObjectMethod(UJNIClass *JNIClass, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIClass || !JNIMethodID)
	{
		return nullptr;
	}
	jobject JObject = Env->CallStaticObjectMethodA(JNIClass->GetJClass(), JNIMethodID->GetJMethodID(), nullptr);
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return nullptr;

	UJNIObject *JNIObject = NewObject<UJNIObject>();
	JNIObject->SetJObject(Env, JObject);
	return JNIObject;
}

FString UJNIComponent::JNICallStaticStringMethod(UJNIClass *JNIClass, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIClass || !JNIMethodID)
	{
		return FString();
	}
	jstring JString = (jstring)Env->CallStaticObjectMethodA(JNIClass->GetJClass(), JNIMethodID->GetJMethodID(), nullptr);
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return FString();

	const char *CString = Env->GetStringUTFChars(JString, nullptr);
	FString ReturnValue = FString(CString);
	Env->ReleaseStringUTFChars(JString, CString);
	return ReturnValue;
}

UJNIObject *UJNIComponent::JNIGetObjectField(UJNIObject *JNIObject, UJNIFieldID *JNIFieldID, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIObject || !JNIFieldID)
	{
		return nullptr;
	}
	jobject JObject = Env->GetObjectField(JNIObject->GetJObject(), JNIFieldID->GetJFieldID());
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return nullptr;

	UJNIObject *JNIRetObject = NewObject<UJNIObject>();
	JNIRetObject->SetJObject(Env, JObject);
	return JNIRetObject;
}

FString UJNIComponent::JNIGetStringField(UJNIObject *JNIObject, UJNIFieldID *JNIFieldID, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIObject || !JNIFieldID)
	{
		return FString();
	}
	jstring JString = (jstring)Env->GetObjectField(JNIObject->GetJObject(), JNIFieldID->GetJFieldID());
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return FString();

	const char *CString = Env->GetStringUTFChars(JString, nullptr);
	FString ReturnValue = FString(CString);
	Env->ReleaseStringUTFChars(JString, CString);
	return ReturnValue;
}

int32 UJNIComponent::JNIGetIntField(UJNIObject *JNIObject, UJNIFieldID *JNIFieldID, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIObject || !JNIFieldID)
	{
		return MIN_int32;
	}
	jint JInt = Env->GetIntField(JNIObject->GetJObject(), JNIFieldID->GetJFieldID());
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return MIN_int32;

	return (int32)JInt;
}

FJNIValue UJNIComponent::JNIGetLongField(UJNIObject *JNIObject, UJNIFieldID *JNIFieldID, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	FJNIValue RetValue;
	RetValue.JLong = MIN_int64;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIObject || !JNIFieldID)
	{
		return RetValue;
	}
	jint JInt = Env->GetLongField(JNIObject->GetJObject(), JNIFieldID->GetJFieldID());
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return RetValue;

	return RetValue;
}


UJNIObject *UJNIComponent::JNINewObject(UJNIClass *JNIClass, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIClass || !JNIMethodID)
	{
		return nullptr;
	}
	jobject JObject = Env->NewObjectA(JNIClass->GetJClass(), JNIMethodID->GetJMethodID(), nullptr);
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return nullptr;

	UJNIObject *JNIObject = NewObject<UJNIObject>();
	JNIObject->SetJObject(Env, JObject);
	return JNIObject;
}

UJNIObject *UJNIComponent::JNICallObjectMethod(UJNIObject *JNIObject, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIObject || !JNIMethodID)
	{
		return nullptr;
	}
	jobject JObject = Env->CallObjectMethodA(JNIObject->GetJObject(), JNIMethodID->GetJMethodID(), nullptr);
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return nullptr;

	UJNIObject *JNIRetObject = NewObject<UJNIObject>();
	JNIRetObject->SetJObject(Env, JObject);
	return JNIRetObject;
}

FString UJNIComponent::JNICallStringMethod(UJNIObject *JNIObject, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIObject || !JNIMethodID)
	{
		return FString();
	}
	jstring JString = (jstring)Env->CallObjectMethodA(JNIObject->GetJObject(), JNIMethodID->GetJMethodID(), nullptr);
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return FString();

	const char *CString = Env->GetStringUTFChars(JString, nullptr);
	FString ReturnValue = FString(CString);
	Env->ReleaseStringUTFChars(JString, CString);
	return ReturnValue;
}

int32 UJNIComponent::JNICallIntMethod(UJNIObject *JNIObject, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env || !JNIObject || !JNIMethodID)
	{
		return MIN_int32;
	}
	jint JInt = Env->CallIntMethodA(JNIObject->GetJObject(), JNIMethodID->GetJMethodID(), nullptr);
	bSuccess = CheckJNIException(Env, Exception);
	if (!bSuccess)
		return MIN_int32;

	return (int32)JInt;
}

UJNIThread *UJNIComponent::JNISpawnThreadMethod(UJNIObject *JNIObject, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception)
{
	bSuccess = false;
	JNIEnv *Env = GetJavaVirtualMachineMainThread();
	if (!Env)// || !JNIObject || !JNIMethodID)
	{
		return nullptr;
	}
	/*jobject JObject = Env->CallObjectMethodA(JNIObject->GetJObject(), JNIMethodID->GetJMethodID(), nullptr);
	if (Env->ExceptionCheck())
	{
		jthrowable JThrowable = Env->ExceptionOccurred();
		UJNIThrowable *JNIThrowable = NewObject<UJNIThrowable>();
		JNIThrowable->SetJObject(Env, JThrowable);
		Env->ExceptionClear();
		Exception = JNIThrowable;

		return nullptr;
	}*/

	UJNIThread *JNIThread = NewObject<UJNIThread>();
	JNIThread->StartJNIThread();
	bSuccess = true;
	return JNIThread;
}