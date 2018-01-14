// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIObject.h"

UJNIObject::UJNIObject()
{
	JNIObjectReference = nullptr;
	JNIObject = nullptr;
	OwningEnv = nullptr;
}

void UJNIObject::SetJObject(JNIEnv *Env, jobject JObject)
{

	JNIEnv *CurrentJEnv = GetJNIEnv(Env);
	if (!CurrentJEnv)
	{
		return;
	}

	JNIObjectReference = Env->NewGlobalRef(JObject);
	JNIObject = JObject;
	OwningEnv = Env;
}

bool UJNIObject::CheckJNIExceptionAndClear()
{
	if (!OwningEnv)
		return false;
	if (OwningEnv->ExceptionCheck())
	{
		OwningEnv->ExceptionClear();
		return true;
	}
	return false;
}

UJNIObject::~UJNIObject()
{
	if (JNIObjectReference)
	{
		JNIEnv *CurrentJEnv = GetJNIEnv(OwningEnv);
		if (!CurrentJEnv)
			return;
		CurrentJEnv->DeleteGlobalRef(JNIObjectReference);
	}
}


