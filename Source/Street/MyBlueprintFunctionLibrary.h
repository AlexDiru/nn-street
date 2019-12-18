// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STREET_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	

	//Doesn't work if the grind rail is bendy as the closest spline point may not contain the closest point on the graph
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Spline")
	static float GetDistanceOnSplineFromWorldLocationDeprecated(const USplineComponent* Spline, FVector WorldLocation, int& closestSplinePoint) {

		float smallestDistanceSq = 9999999999;
		closestSplinePoint = 0;

		for (int i = 0; i < Spline->GetNumberOfSplinePoints(); i++) {
			float currentDistanceSq = FVector::DistSquared(WorldLocation, Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
			if (currentDistanceSq < smallestDistanceSq) {
				smallestDistanceSq = currentDistanceSq;
				closestSplinePoint = i;
			}
		}

		smallestDistanceSq = 9999999999;

		//Now we have the closest spline point, we need to check from the previous spline point to the next spline point to narrow down a position
		//Catches: Previous spline point >= 0 and Next spline point < NumSplinePoints()
		int previousSplinePoint = (closestSplinePoint == 0) ? 0 : closestSplinePoint - 1;
		int nextSplinePoint = (closestSplinePoint == Spline->GetNumberOfSplinePoints() - 1) ? Spline->GetNumberOfSplinePoints() - 1 : closestSplinePoint + 1;
		float closestDistance = 0;


		//UE_LOG(LogTemp, Warning, TEXT("Num Spline Points: %d [%d] [%d -> %d]"), Spline->GetNumberOfSplinePoints(), closestSplinePoint, previousSplinePoint, nextSplinePoint);

		for (int i = Spline->GetDistanceAlongSplineAtSplinePoint(previousSplinePoint); i <= Spline->GetDistanceAlongSplineAtSplinePoint(nextSplinePoint); i++) {
			float currentDistanceSq = FVector::DistSquared(WorldLocation, Spline->GetLocationAtDistanceAlongSpline(i, ESplineCoordinateSpace::World));
			if (currentDistanceSq < smallestDistanceSq) {
				smallestDistanceSq = currentDistanceSq;
				closestDistance = i;
			}
		}

		return closestDistance;
	}

	//Could still be inaccurate if rail is really long and bendy
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Spline")
	static float GetDistanceOnSplineFromWorldLocation(const USplineComponent* Spline, FVector WorldLocation) {

		float smallestDistanceSq = 9999999999;

		float splineDistance = Spline->GetDistanceAlongSplineAtSplinePoint(Spline->GetNumberOfSplinePoints() - 1);
		float stepAmount = splineDistance / 100;
		float closestDistance = -1;

		float d;

		for (d = 0; d <= splineDistance; d += stepAmount) {
			float currentDistanceSq = FVector::DistSquared(WorldLocation, Spline->GetLocationAtDistanceAlongSpline(d, ESplineCoordinateSpace::World));
			if (currentDistanceSq < smallestDistanceSq) {
				smallestDistanceSq = currentDistanceSq;
				closestDistance = d;
			}
		}

		float lb = (closestDistance - stepAmount < 0) ? 0 : closestDistance - stepAmount;
		float ub = (closestDistance + stepAmount > splineDistance) ? splineDistance : closestDistance + stepAmount;

		for (d = lb; d <= ub; d += (stepAmount / 100)) {
			float currentDistanceSq = FVector::DistSquared(WorldLocation, Spline->GetLocationAtDistanceAlongSpline(d, ESplineCoordinateSpace::World));
			if (currentDistanceSq < smallestDistanceSq) {
				smallestDistanceSq = currentDistanceSq;
				closestDistance = d;
			}
		}

		return closestDistance;
		
	}


	/*UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Spline")
	static float GetDistanceAtSplinePoint(const USplineComponent* Spline, int SplinePoint, int& closestSplinePoint) {
		FVector worldLoc = Spline->GetTransformAtSplinePoint(SplinePoint, ESplineCoordinateSpace::World).GetLocation();
		return GetDistanceOnSplineFromWorldLocation(Spline, worldLoc, closestSplinePoint);
	}

	//Optimise This!!!???
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Spline")
	static void GetBoundingSplinePoints(const USplineComponent* Spline, FVector Location, bool TravellingForwardAlongSpline, int& splinePoint1, int& splinePoint2) {
		int closestSplinePoint;
		float PlayerDistance = GetDistanceOnSplineFromWorldLocation(Spline, Location, closestSplinePoint);

		int s1 = 0, s2 = 1;
		
		for (int i = 0; i < Spline->GetNumberOfSplinePoints()-1; i++) {
			if (PlayerDistance >= GetDistanceAtSplinePoint(Spline, i, closestSplinePoint)) {
				if (PlayerDistance < GetDistanceAtSplinePoint(Spline, i + 1, closestSplinePoint)) {
					s1 = i;
					s2 = i + 1;
					break;
				}
			}
		}

		if (TravellingForwardAlongSpline) {
			splinePoint1 = s1;
			splinePoint2 = s2;
		} else {
			splinePoint1 = s2;
			splinePoint2 = s1;
		}
	}*/
	
	
};
