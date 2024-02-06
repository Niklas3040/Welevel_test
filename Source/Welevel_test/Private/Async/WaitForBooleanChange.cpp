// Fill out your copyright notice in the Description page of Project Settings.

#include "Welevel_test/Public/Async/WaitForBooleanChange.h"


UWaitForBooleanChange* UWaitForBooleanChange::WaitForBooleanChange(const UObject* WorldContext,
                                                                   AListeningActor* ListeningActor, ATargetActor* TargetActor)
{
	UWorld* ContextWorld = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if (!ContextWorld)
	{
		return nullptr;
	}

	UWaitForBooleanChange* NewAction = NewObject<UWaitForBooleanChange>();
	NewAction->ContextWorld = ContextWorld;
	NewAction->ListeningActor = ListeningActor;
	NewAction->TargetActor = TargetActor;
	NewAction->RegisterWithGameInstance(ContextWorld->GetGameInstance());

	return NewAction;
}

void UWaitForBooleanChange::CallOnValueChanged(bool Value)
{
	OnValueChange.Broadcast(Value);
	SetReadyToDestroy();
}

void UWaitForBooleanChange::Activate()
{
	if (TargetActor)
		TargetActor->OnValueChangedDelegate.BindDynamic(this, &UWaitForBooleanChange::CallOnValueChanged);
}

