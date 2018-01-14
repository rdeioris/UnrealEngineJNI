// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIFieldID.h"



UJNIFieldID::UJNIFieldID()
{
	JNIFieldID = nullptr;
	OwningEnv = nullptr;
}



void UJNIFieldID::SetJFieldID(JNIEnv *Env, jfieldID JFieldID)
{

	JNIEnv *CurrentJEnv = GetJNIEnv(Env);
	if (!CurrentJEnv)
	{
		return;
	}

	JNIFieldID = JFieldID;
	OwningEnv = Env;
}
