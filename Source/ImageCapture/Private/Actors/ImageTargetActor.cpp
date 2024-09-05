// Fill out your copyright notice in the Description page of Project Settings.


#include "ImageCapture/Public/Actors/ImageTargetActor.h"

#include "ImageCapture/Public/Components/ImagePointComponent.h"


// Sets default values
AImageTargetActor::AImageTargetActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AImageTargetActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AImageTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<UImagePointComponent*> AImageTargetActor::GetAllImagePoints() const
{
	TArray<UImagePointComponent*> res;
	GetComponents(UImagePointComponent::StaticClass(), res);
	return res;
}

TArray<FVector> AImageTargetActor::GetImagePointsLocations() const
{
	TArray<UImagePointComponent*> components = GetAllImagePoints();

	TArray<FVector> res;
	for (UImagePointComponent* entity : components)
	{
		res.Add(entity->GetComponentLocation());
	}
	return res;
}
