// Fill out your copyright notice in the Description page of Project Settings.


#include "Welevel_test/public/TargetActor.h"

// Sets default values
ATargetActor::ATargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void ATargetActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATargetActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATargetActor, bListeningBool);
}

void ATargetActor::SetListeningBool(bool ListeningBool)
{
	this->bListeningBool = ListeningBool;
	OnValueChangedDelegate.ExecuteIfBound(ListeningBool);
}

void ATargetActor::OnRepListeningBool()
{
	OnValueChangedDelegate.ExecuteIfBound(bListeningBool);
}

// Called every frame
void ATargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

