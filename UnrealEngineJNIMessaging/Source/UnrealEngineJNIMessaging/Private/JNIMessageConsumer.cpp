// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIMessageConsumer.h"


// Sets default values for this component's properties
UJNIMessageConsumer::UJNIMessageConsumer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJNIMessageConsumer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJNIMessageConsumer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!OnMessageReceived.IsBound())
		return;

	if (QueueToConsume.IsEmpty())
		return;

	FUnrealEngineJNIMessagingModule &Module = FModuleManager::GetModuleChecked<FUnrealEngineJNIMessagingModule>("UnrealEngineJNIMessaging");

	FString Message;
	bool bMessageReceived = Module.JNIDequeue(QueueToConsume, Message);

	if (bMessageReceived)
	{
		OnMessageReceived.Broadcast(Message);
	}
}

