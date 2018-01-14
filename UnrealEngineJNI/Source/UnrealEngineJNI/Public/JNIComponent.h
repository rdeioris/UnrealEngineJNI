// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnrealEngineJNI.h"
#include "JNIClass.h"
#include "JNIThrowable.h"
#include "JNIMethodID.h"
#include "JNIFieldID.h"
#include "JNIValue.h"
#include "JNIThread.h"
#include "JNIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FJNIExceptionDelegate, FString, ClassName, FString, Message);


UCLASS(ClassGroup = (JNI), meta = (BlueprintSpawnableComponent))
class UNREALENGINEJNI_API UJNIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UJNIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	JNIEnv *GetJavaVirtualMachineMainThread();

	bool CheckJNIException(JNIEnv *Env, UJNIThrowable *&Exception);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FJNIExceptionDelegate OnJNIException;

	UFUNCTION(BlueprintCallable)
	UJNIClass *JNIFindClass(FString ClassName, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable)
	UJNIMethodID *JNIGetMethodID(UJNIClass *JNIClass, FString MethodName, FString Signature, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable)
	UJNIMethodID *JNIGetStaticMethodID(UJNIClass *JNIClass, FString MethodName, FString Signature, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable)
	UJNIFieldID *JNIGetFieldID(UJNIClass *JNIClass, FString FieldName, FString Signature, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable)
	UJNIFieldID *JNIGetStaticFieldID(UJNIClass *JNIClass, FString FieldName, FString Signature, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="JNIArguments"))
	UJNIObject *JNICallStaticObjectMethod(UJNIClass *JNIClass, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "JNIArguments"))
	FString JNICallStaticStringMethod(UJNIClass *JNIClass, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable)
	UJNIObject *JNIGetObjectField(UJNIObject *JNIObject, UJNIFieldID *JNIFieldID, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable)
	FString JNIGetStringField(UJNIObject *JNIObject, UJNIFieldID *JNIFieldID, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable)
	int32 JNIGetIntField(UJNIObject *JNIObject, UJNIFieldID *JNIFieldID, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable)
	FJNIValue JNIGetLongField(UJNIObject *JNIObject, UJNIFieldID *JNIFieldID, bool & bSuccess, UJNIThrowable *&Exception);
	
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "JNIArguments"))
	UJNIObject *JNINewObject(UJNIClass *JNIClass, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception);
	
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "JNIArguments"))
	UJNIObject *JNICallObjectMethod(UJNIObject *JNIObject, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "JNIArguments"))
	FString JNICallStringMethod(UJNIObject *JNIObject, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "JNIArguments"))
	int32 JNICallIntMethod(UJNIObject *JNIObject, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception);

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "JNIArguments"))
	UJNIThread *JNISpawnThreadMethod(UJNIObject *JNIObject, UJNIMethodID *JNIMethodID, const TArray<FJNIValue>& JNIArguments, bool & bSuccess, UJNIThrowable *&Exception);
};
