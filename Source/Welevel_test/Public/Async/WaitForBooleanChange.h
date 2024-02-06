// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Welevel_test/Public/ListeningActor.h"
#include "Welevel_test/Public/TargetActor.h"
#include "Engine/CancellableAsyncAction.h"
#include "WaitForBooleanChange.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChange, bool, Value);

/**
 * 
 */
UCLASS()
class WELEVEL_TEST_API UWaitForBooleanChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/**
	* Waits until the boolean changes value and returns it.
	* @param ListeningActor ListeningActor to listen from
	* @param TargetActor TargetActor to listen to
	* @param WorldContext Object from which the world will be derived.
	*/
	UFUNCTION(BlueprintCallable, DisplayName="Wait for Boolean Change", meta=(WorldContext="WorldContext", BlueprintInternalUseOnly="true"))
	static UWaitForBooleanChange* WaitForBooleanChange(const UObject* WorldContext, AListeningActor* ListeningActor, ATargetActor* TargetActor);

	UFUNCTION()
	void CallOnValueChanged(bool Value);

	UPROPERTY(BlueprintAssignable)
	FOnValueChange OnValueChange;

	virtual void Activate() override;

private:
	TWeakObjectPtr<UWorld> ContextWorld = nullptr;
	
	UPROPERTY()
	AListeningActor* ListeningActor;
	
	UPROPERTY()
	ATargetActor* TargetActor;
};
