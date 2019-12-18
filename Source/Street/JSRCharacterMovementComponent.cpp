// Fill out your copyright notice in the Description page of Project Settings.

#include "Street.h"
#include "JSRCharacterMovementComponent.h"


// Sets default values for this component's properties
UJSRCharacterMovementComponent::UJSRCharacterMovementComponent()
	: Super()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true;

	// ...

	this->MaxWalkSpeed = 480;
	this->JumpZVelocity = 600;
	this->AirControl = 1;
	this->RotationRate.Yaw = 540;
	this->bOrientRotationToMovement = true;
	this->NavAgentProps.AgentHeight = 192;
	this->NavAgentProps.AgentHeight = 42;
}


// Called when the game starts
void UJSRCharacterMovementComponent::BeginPlay()
{

	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Init JSR Character Movement Component"));
	
}


// Called every frame
void UJSRCharacterMovementComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UJSRCharacterMovementComponent::ApplyDownwardForce(float DeltaSeconds)
{
	if (StandingDownwardForceScale != 0.0f && CurrentFloor.HitResult.IsValidBlockingHit())
	{
		UPrimitiveComponent* BaseComp = CurrentFloor.HitResult.GetComponent();
		


		FVector DownVector = BaseComp->GetUpVector().RotateAngleAxis(180, FVector(1, 0, 0));
		const FVector Gravity = FVector(GetGravityZ() * DownVector.X, GetGravityZ() * DownVector.Y, GetGravityZ() * DownVector.Z);

		UE_LOG(LogTemp, Warning, TEXT("Using new gravity method"));

		if (BaseComp && BaseComp->IsAnySimulatingPhysics() && !Gravity.IsZero())
		{
			//BaseComp->AddForceAtLocation(Gravity * Mass * StandingDownwardForceScale, CurrentFloor.HitResult.ImpactPoint, CurrentFloor.HitResult.BoneName);
		}
	}
}


bool UJSRCharacterMovementComponent::IsWalkable(const FHitResult& Hit) const
{
	/*if (!Hit.IsValidBlockingHit())
	{
		// No hit, or starting in penetration
		return false;
	}

	// Never walk up vertical surfaces.
	if (Hit.ImpactNormal.Z < KINDA_SMALL_NUMBER)
	{
		return false;
	}

	float TestWalkableZ = WalkableFloorZ;

	// See if this component overrides the walkable floor z.
	const UPrimitiveComponent* HitComponent = Hit.Component.Get();
	if (HitComponent)
	{
		const FWalkableSlopeOverride& SlopeOverride = HitComponent->GetWalkableSlopeOverride();
		TestWalkableZ = SlopeOverride.ModifyWalkableFloorZ(TestWalkableZ);
	}

	// Can't walk on this surface if it is too steep.
	if (Hit.ImpactNormal.Z < TestWalkableZ)
	{
		return false;
	}*/

	return true;
}

