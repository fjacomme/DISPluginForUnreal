// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDISComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UOpenDISComponent::UOpenDISComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDISComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UOpenDISComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Check if dead reckoning should be performed
	if (PerformDeadReckoning)
	{
		//Check if dead reckoning is supported. Broadcast dead reckoning update if it is
		if (DeadReckoning(mostRecentEntityStatePDU, DeltaTime, deadReckonedPDU))
		{
			OnDeadReckoningUpdate.Broadcast(deadReckonedPDU);
		}
		else
		{
			//Turn dead reckoning off if it is not supported
			PerformDeadReckoning = false;
		}
	}

	//Check if ground clamping is enabled
	if (PerformGroundClamping)
	{
		FVector groundClampLocation;
		FRotator groundClampRotation;

		//If ground clamping is supported and a proper hit returned, update the actor's location/rotation
		if (ApplyGroundClamping(groundClampLocation, groundClampRotation))
		{
			GetOwner()->SetActorLocationAndRotation(groundClampLocation, groundClampRotation);
		}
	}
}

void UOpenDISComponent::HandleEntityStatePDU(FEntityStatePDU NewEntityStatePDU)
{
	//Check if the entity has been deactivated
	if (NewEntityStatePDU.EntityAppearance == 1)
	{
		GetOwner()->Destroy();
	}

	latestPDUTimestamp = FDateTime::Now();
	mostRecentEntityStatePDU = NewEntityStatePDU;

	EntityType = NewEntityStatePDU.EntityType;
	EntityID = NewEntityStatePDU.EntityID;

	GetOwner()->SetLifeSpan(DISHeartbeat);

	OnReceivedEntityStatePDU.Broadcast(NewEntityStatePDU);
}

void UOpenDISComponent::HandleFirePDU(FFirePDU FirePDUIn)
{
	OnReceivedFirePDU.Broadcast(FirePDUIn);
}

void UOpenDISComponent::HandleDetonationPDU(FDetonationPDU DetonationPDUIn)
{
	OnReceivedDetonationPDU.Broadcast(DetonationPDUIn);
}

void UOpenDISComponent::HandleRemoveEntityPDU(FRemoveEntityPDU RemoveEntityPDUIn)
{
	OnReceivedRemoveEntityPDU.Broadcast(RemoveEntityPDUIn);
}

bool UOpenDISComponent::DeadReckoning(FEntityStatePDU EntityPDUToDeadReckon, float DeltaTime, FEntityStatePDU& DeadReckonedEntityPDU)
{
	DeadReckonedEntityPDU = EntityPDUToDeadReckon;
	bool supported = true;

	// TODO: Only perform dead reckoning on entities that are being received from the network.
	// I don't think we would want to perform dead reckoning on entities that we own/are sending.
	// Or do we want to leave this up to the user and if they have 'PerformDeadReckoning' enabled.

	switch (EntityPDUToDeadReckon.DeadReckoningParameters.DeadReckoningAlgorithm) {
	case 1:
		//static so it doesn't matter if we update or not so just leave it as unsupported
		supported = false;
		break;
	case 2:
	{
		FVector locVelxDeltaTime = (EntityPDUToDeadReckon.EntityLinearVelocity * DeltaTime);

		DeadReckonedEntityPDU.EntityLocationDouble[0] = EntityPDUToDeadReckon.EntityLocationDouble[0] + locVelxDeltaTime[0];
		DeadReckonedEntityPDU.EntityLocationDouble[1] = EntityPDUToDeadReckon.EntityLocationDouble[1] + locVelxDeltaTime[1];
		DeadReckonedEntityPDU.EntityLocationDouble[2] = EntityPDUToDeadReckon.EntityLocationDouble[2] + locVelxDeltaTime[2];
		break;
	}
	case 3:
	{
		DeadReckonedEntityPDU.EntityOrientation = GetRotationForDeadReckoning(EntityPDUToDeadReckon, DeltaTime);

		FVector locVelxDeltaTime = (EntityPDUToDeadReckon.EntityLinearVelocity * DeltaTime);

		DeadReckonedEntityPDU.EntityLocationDouble[0] = EntityPDUToDeadReckon.EntityLocationDouble[0] + locVelxDeltaTime[0];
		DeadReckonedEntityPDU.EntityLocationDouble[1] = EntityPDUToDeadReckon.EntityLocationDouble[1] + locVelxDeltaTime[1];
		DeadReckonedEntityPDU.EntityLocationDouble[2] = EntityPDUToDeadReckon.EntityLocationDouble[2] + locVelxDeltaTime[2];
		break;
	}
	case 4:
	{
		DeadReckonedEntityPDU.EntityOrientation = GetRotationForDeadReckoning(EntityPDUToDeadReckon, DeltaTime);

		FVector locVelxDeltaTime = (EntityPDUToDeadReckon.EntityLinearVelocity * DeltaTime);
		FVector locHalfAccelxDeltaTSquarred = 0.5 * (EntityPDUToDeadReckon.DeadReckoningParameters.EntityLinearAcceleration * (DeltaTime * DeltaTime));

		DeadReckonedEntityPDU.EntityLocationDouble[0] = EntityPDUToDeadReckon.EntityLocationDouble[0] + locVelxDeltaTime[0] + locHalfAccelxDeltaTSquarred[0];
		DeadReckonedEntityPDU.EntityLocationDouble[1] = EntityPDUToDeadReckon.EntityLocationDouble[1] + locVelxDeltaTime[1] + locHalfAccelxDeltaTSquarred[1];
		DeadReckonedEntityPDU.EntityLocationDouble[2] = EntityPDUToDeadReckon.EntityLocationDouble[2] + locVelxDeltaTime[2] + locHalfAccelxDeltaTSquarred[2];
		break;
	}
	case 5:
	{
		FVector locVelxDeltaTime = (EntityPDUToDeadReckon.EntityLinearVelocity * DeltaTime);
		FVector locHalfAccelxDeltaTSquarred = 0.5 * (EntityPDUToDeadReckon.DeadReckoningParameters.EntityLinearAcceleration * (DeltaTime * DeltaTime));

		DeadReckonedEntityPDU.EntityLocationDouble[0] = EntityPDUToDeadReckon.EntityLocationDouble[0] + locVelxDeltaTime[0] + locHalfAccelxDeltaTSquarred[0];
		DeadReckonedEntityPDU.EntityLocationDouble[1] = EntityPDUToDeadReckon.EntityLocationDouble[1] + locVelxDeltaTime[1] + locHalfAccelxDeltaTSquarred[1];
		DeadReckonedEntityPDU.EntityLocationDouble[2] = EntityPDUToDeadReckon.EntityLocationDouble[2] + locVelxDeltaTime[2] + locHalfAccelxDeltaTSquarred[2];
		break;
	}
	default:
		supported = false;
		break;
	}

	return supported;
}

FRotator UOpenDISComponent::GetRotationForDeadReckoning(FEntityStatePDU EntityPDUToDeadReckon, float DeltaTime)
{
	// TODO: Implement DeadReckoning for the rotation change of the actor.
	// This should probably stay in Euler and leave conversions from euler to UE4 rotation to the end user of the plugin.

	return EntityPDUToDeadReckon.EntityOrientation;
}

bool UOpenDISComponent::ApplyGroundClamping_Implementation(FVector& ClampLocation, FRotator& ClampRotation)
{
	// TODO: Only perform ground clamping on entities that are being received from the network.
	// I don't think we would want to perform ground clamping on entities that we own/are sending.
	// Or do we want to leave this up to the user and if they have 'PerformGroundClamping' enabled.

	// TODO: Only perform ground clamping once for static objects that will never move.

	bool groundClampSuccessful = false;
	//Verify the entity is of the ground domain and that it is not a munition
	if (EntityType.Domain == 1 && EntityType.EntityKind != 2)
	{
		FHitResult lineTraceHitResult;
		// TODO: Get the ENU of the actor rather than the up vector to verify that the line trace is always going towards the terrain
		FVector actorLocation = GetOwner()->GetActorLocation();
		FVector endLocation = (GetOwner()->GetActorUpVector() * -100000) + actorLocation;
		FVector aboveActorStartLocation = (GetOwner()->GetActorUpVector() * 100000) + actorLocation;

		FCollisionQueryParams queryParams = FCollisionQueryParams(FName("Ground Clamping"), false, GetOwner());

		//Find colliding point above/below the actor
		if (GetWorld()->LineTraceSingleByChannel(lineTraceHitResult, aboveActorStartLocation, endLocation, GoundClampingCollisionChannel, queryParams))
		{
			ClampLocation = lineTraceHitResult.Location;
			//Calculate what the new forward and right vectors should be based on the impact normal
			FVector newForward = FVector::CrossProduct(GetOwner()->GetActorRightVector(), lineTraceHitResult.ImpactNormal);
			FVector newRight = FVector::CrossProduct(lineTraceHitResult.ImpactNormal, newForward);

			ClampRotation = UKismetMathLibrary::MakeRotationFromAxes(newForward, newRight, lineTraceHitResult.ImpactNormal);

			groundClampSuccessful = true;
		}
	}
	else
	{
		PerformGroundClamping = false;
	}

	return groundClampSuccessful;
}