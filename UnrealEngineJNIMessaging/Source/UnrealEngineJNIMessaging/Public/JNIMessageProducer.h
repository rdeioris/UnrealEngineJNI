// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnrealEngineJNIMessaging.h"
#include "JNIMessageProducer.generated.h"


UCLASS( ClassGroup=(JNIMessaging), meta=(BlueprintSpawnableComponent) )
class UNREALENGINEJNIMESSAGING_API UJNIMessageProducer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJNIMessageProducer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool Enqueue(FString Queue, FString Message);

	UFUNCTION(BlueprintCallable)
	void Empty(FString Queue);
	
};
