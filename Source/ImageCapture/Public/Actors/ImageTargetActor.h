// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImageTargetActor.generated.h"

class UImagePointComponent;

UCLASS()
class IMAGECAPTURE_API AImageTargetActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AImageTargetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	TArray<UImagePointComponent*> GetAllImagePoints() const;

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetImagePointsWorldLocations() const;

	UFUNCTION(BlueprintCallable)
	void ConvertWorldLocationToScreen(const TArray<FVector>& InLocations, TArray<FVector2D>& OutViewPortLocation);

	UFUNCTION(BlueprintCallable)
	void CalculateBoundingSquare(const TArray<FVector2D>& Points, FVector2D& OutCenter, float& OutHalfSize);
};
