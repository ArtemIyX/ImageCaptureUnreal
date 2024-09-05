// Fill out your copyright notice in the Description page of Project Settings.


#include "ImageCapture/Public/Actors/ImageTargetActor.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "ImageCapture/Public/Components/ImagePointComponent.h"
#include "Kismet/GameplayStatics.h"


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

TArray<FVector> AImageTargetActor::GetImagePointsWorldLocations() const
{
	TArray<UImagePointComponent*> components = GetAllImagePoints();

	TArray<FVector> res;
	for (UImagePointComponent* entity : components)
	{
		res.Add(entity->GetComponentLocation());
	}
	return res;
}

void AImageTargetActor::ConvertWorldLocationToScreen(const TArray<FVector>& InLocations,
                                                     TArray<FVector2D>& OutViewPortLocation)
{
	OutViewPortLocation.Empty();
	OutViewPortLocation.Reserve(InLocations.Num());
	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	for (FVector location : InLocations)
	{
		FVector2D screenPos;
		if (UGameplayStatics::ProjectWorldToScreen(pc, location, screenPos))
		{
			FVector2D viewPortPos;
			USlateBlueprintLibrary::ScreenToViewport(this, screenPos, viewPortPos);
			OutViewPortLocation.Add(viewPortPos);
		}
	}
}

void AImageTargetActor::CalculateBoundingSquare(const TArray<FVector2D>& Points, FVector2D& OutCenter,
                                                float& OutHalfSize)
{
	if (Points.Num() == 0)
	{
		// No points, return zero values
		OutCenter = FVector2D(0.0f, 0.0f);
		OutHalfSize = 0.0f;
		return;
	}

	// Initialize min and max values
	FVector2D Min(TNumericLimits<double>::Max(), TNumericLimits<double>::Max());
	FVector2D Max(TNumericLimits<double>::Min(), TNumericLimits<double>::Min());

	// Find the min and max bounds
	for (const FVector2D& Point : Points)
	{
		if (Point.X < Min.X) Min.X = Point.X;
		if (Point.Y < Min.Y) Min.Y = Point.Y;

		if (Point.X > Max.X) Max.X = Point.X;
		if (Point.Y > Max.Y) Max.Y = Point.Y;
	}

	// Calculate the center of the bounding square
	OutCenter = (Min + Max) / 2.0f;

	// Calculate the size (make the bounding square large enough to fit all points)
	float SizeX = Max.X - Min.X;
	float SizeY = Max.Y - Min.Y;

	// The size of the square will be the largest of SizeX or SizeY (to cover all points)
	float SquareSize = FMath::Max(SizeX, SizeY);

	// Half-size is half of the square's size (distance from center to side)
	OutHalfSize = SquareSize / 2.0f;
}
