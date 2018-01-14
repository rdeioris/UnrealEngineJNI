// Fill out your copyright notice in the Description page of Project Settings.

#include "JNIMessageProducer.h"


// Sets default values for this component's properties
UJNIMessageProducer::UJNIMessagingProducer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UJNIMessageProducer::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UJNIMessageProducer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UJNIMessageProducer::Enqueue(FString Queue, FString Message)
{
	FUnrealEngineJNIMessagingModule &Module = FModuleManager::GetModuleChecked<FUnrealEngineJNIMessagingModule>("UnrealEngineJNIMessaging");
	return Module.JNIEnqueue(Queue, Message);
}

