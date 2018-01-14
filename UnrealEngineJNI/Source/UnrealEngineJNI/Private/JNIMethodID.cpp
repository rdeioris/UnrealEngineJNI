// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIMethodID.h"

UJNIMethodID::UJNIMethodID()
{
	JNIMethodID = nullptr;
	OwningEnv = nullptr;
}



void UJNIMethodID::SetJMethodID(JNIEnv *Env, jmethodID JMethodID)
{

	JNIEnv *CurrentJEnv = GetJNIEnv(Env);
	if (!CurrentJEnv)
	{
		return;
	}

	JNIMethodID = JMethodID;
	OwningEnv = Env;
}

