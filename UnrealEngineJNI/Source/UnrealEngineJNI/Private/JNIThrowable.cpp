// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIThrowable.h"


FString UJNIThrowable::GetJNIExceptionMessage()
{
	JNIEnv *Env = GetJNIEnv(OwningEnv);
	if (!Env)
		return FString();

	jclass ExceptionClass = Env->GetObjectClass(JNIObject);
	if (CheckJNIExceptionAndClear())
		return FString();

	jmethodID getMessageMID = Env->GetMethodID(ExceptionClass, "getMessage", "()Ljava/lang/String;");
	if (CheckJNIExceptionAndClear())
		return FString();

	jstring Message = (jstring)Env->CallObjectMethod(JNIObject, getMessageMID);
	if (CheckJNIExceptionAndClear())
		return FString();

	const char *StrMessage = Env->GetStringUTFChars(Message, NULL);
	if (!StrMessage)
		return FString();

	FString ExceptionMessage = FString(StrMessage);

	Env->ReleaseStringUTFChars(Message, StrMessage);

	return ExceptionMessage;

}

FString UJNIThrowable::GetJNIExceptionClassName()
{
	JNIEnv *Env = GetJNIEnv(OwningEnv);
	if (!Env)
		return FString();

	jclass ExceptionClass = Env->GetObjectClass(JNIObject);
	if (CheckJNIExceptionAndClear())
		return FString();

	jmethodID getNameMID = Env->GetMethodID(Env->FindClass("java/lang/Class"), "getName", "()Ljava/lang/String;");
	if (CheckJNIExceptionAndClear())
		return FString();

	jstring Message = (jstring)Env->CallObjectMethod(ExceptionClass, getNameMID);
	if (CheckJNIExceptionAndClear())
		return FString();

	const char *StrMessage = Env->GetStringUTFChars(Message, nullptr);
	if (!StrMessage)
		return FString();

	FString ExceptionMessage = FString(StrMessage);

	Env->ReleaseStringUTFChars(Message, StrMessage);

	return ExceptionMessage;

}