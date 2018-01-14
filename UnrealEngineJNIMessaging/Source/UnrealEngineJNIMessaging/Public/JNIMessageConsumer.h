// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnrealEngineJNIMessaging.h"
#include "JNIMessageConsumer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FJNIMessageConsumerDelegate, FString, Message);


UCLASS( ClassGroup=(JNIMessaging), meta=(BlueprintSpawnableComponent) )
class UNREALENGINEJNIMESSAGING_API UJNIMessageConsumer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJNIMessageConsumer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	FString QueueToConsume;

	UPROPERTY(BlueprintAssignable)
	FJNIMessageConsumerDelegate OnMessageReceived;
};
