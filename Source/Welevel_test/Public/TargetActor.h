// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "TargetActor.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnValueChangedDelegate, bool, Value);


UCLASS()
class WELEVEL_TEST_API ATargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetActor();
	
	FOnValueChangedDelegate OnValueChangedDelegate;

protected:
	virtual void BeginPlay() override;

	//has to be overriden to replicate Properties
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;
	
	// bListening Bool executes the SetListeningBool function every time a new value is assigned through Blueprints
	// When updating the value of bListeningBool through blueprints this implementation should be enough
	// For Changing the value in C++ you also have to execute this SetterFunction instead of using "=" (e.g SetListeningBool(true) instead of bListeningBool=true)
	// For C++ only Projects this could be replaced by "__declspec(property(get=getListeningBool, put=SetListeningBool)) bool bListeningBool = false"
	// which would execute the Setter Function automatically anytime the value of bListeningBool is changed.
	// Since this cant be used as a UPROPERTY it cant be exposed to blueprints or replicated
	// I would recommend using this approach and using the Setter-Function explicitly. 
	UPROPERTY(BlueprintSetter=SetListeningBool, EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRepListeningBool)
	bool bListeningBool = false;

public:
	//This Setter should be used on the Server
	UFUNCTION(BlueprintSetter)
	void SetListeningBool(bool ListeningBool);

	//This OnRep Function is used on the clients when the server sends an update
	UFUNCTION()
	void OnRepListeningBool();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
