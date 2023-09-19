// Copyright 2022 Gaming Research Integration for Learning Lab. All Rights Reserved.

#pragma once
//dis headers
#include <dis6/Pdu.h>
#include <utils/PDUBank.h>
#include <utils/DataStream.h>

//PDU type headers, add as more pdu types are support!
#include <dis6/EntityStatePdu.h>   
#include <dis6/FirePdu.h>
#include <dis6/DetonationPdu.h>
#include <dis6/RemoveEntityPdu.h>
#include <dis6/EntityStateUpdatePdu.h>
#include <dis6/StartResumePdu.h>
#include <dis6/StopFreezePdu.h>

#include "Kismet/KismetStringLibrary.h"
#include "CoreMinimal.h"
#include "DISEnumsAndStructs.generated.h"

UENUM(BlueprintType)
enum class EEntityStateSendingMode : uint8
{
	None						UMETA(Tooltip = "Don't send out any automatic Entity State PDU updates."),
	EntityStatePDU				UMETA(Tooltip = "Send out automatic Entity State PDU updates."),
	EntityStateUpdatePDU		UMETA(Tooltip = "Send out automatic Entity State Update PDU updates.")
};

UENUM(BlueprintType)
enum class EDISCullingMode : uint8
{
	None						UMETA(Tooltip = "Don't cull any DIS updates."),
	CullDeadReckoning			UMETA(Tooltip = "Cull only dead reckoning updates."),
	CullAll						UMETA(Tooltip = "Cull all DIS updates. Currently only performs dead reckoning culling.")
};

UENUM(BlueprintType)
enum class EGroundClampingMode : uint8
{
	None						UMETA(Tooltip = "Never ground clamp this entity."),
	GroundClampWithDISOptions	UMETA(Tooltip = "Ground clamp this entity if it is of the ground domain and not a munition."),
	AlwaysGroundClamp			UMETA(Tooltip = "Always ground clamp this entity.")
};

UENUM(BlueprintType)
enum class EDeadReckoningAlgorithm : uint8
{
	Other		UMETA(Tooltip = "Using a custom DR algorithm."),
	Static		UMETA(Tooltip = "Static. Entity does not move."),
	FPW			UMETA(Tooltip = "Fixed Position World"),
	RPW			UMETA(Tooltip = "Rotation Position World"),
	RVW			UMETA(Tooltip = "Rotation Velocity World"),
	FVW			UMETA(Tooltip = "Fixed Velocity World"),
	FPB			UMETA(Tooltip = "Fixed Position Body"),
	RPB			UMETA(Tooltip = "Rotation Position Body"),
	RVB			UMETA(Tooltip = "Rotation Velocity Body"),
	FVB			UMETA(Tooltip = "Fixed Velocity Body")
};

UENUM(BlueprintType)
enum class EForceID : uint8
{
	Other		UMETA(DisplayName = "Other"),
	Friendly	UMETA(DisplayName = "Friendly"),
	Opposing	UMETA(DisplayName = "Opposing"),
	Neutral		UMETA(DisplayName = "Neutral"),
	Friendly2	UMETA(DisplayName = "Friendly 2"),
	Opposing2	UMETA(DisplayName = "Opposing 2"),
	Neutral2	UMETA(DisplayName = "Neutral 2"),
	Friendly3	UMETA(DisplayName = "Friendly 3"),
	Opposing3	UMETA(DisplayName = "Opposing 3"),
	Neutral3	UMETA(DisplayName = "Neutral 3"),
	Friendly4	UMETA(DisplayName = "Friendly 4"),
	Opposing4	UMETA(DisplayName = "Opposing 4"),
	Neutral4	UMETA(DisplayName = "Neutral 4"),
	Friendly5	UMETA(DisplayName = "Friendly 5"),
	Opposing5	UMETA(DisplayName = "Opposing 5"),
	Neutral5	UMETA(DisplayName = "Neutral 5"),
	Friendly6	UMETA(DisplayName = "Friendly 6"),
	Opposing6	UMETA(DisplayName = "Opposing 6"),
	Neutral6	UMETA(DisplayName = "Neutral 6"),
	Friendly7	UMETA(DisplayName = "Friendly 7"),
	Opposing7	UMETA(DisplayName = "Opposing 7"),
	Neutral7	UMETA(DisplayName = "Neutral 7"),
	Friendly8	UMETA(DisplayName = "Friendly 8"),
	Opposing8	UMETA(DisplayName = "Opposing 8"),
	Neutral8	UMETA(DisplayName = "Neutral 8"),
	Friendly9	UMETA(DisplayName = "Friendly 9"),
	Opposing9	UMETA(DisplayName = "Opposing 9"),
	Neutral9	UMETA(DisplayName = "Neutral 9"),
	Friendly10	UMETA(DisplayName = "Friendly 10"),
	Opposing10	UMETA(DisplayName = "Opposing 10"),
	Neutral10	UMETA(DisplayName = "Neutral 10")
};

UENUM(BlueprintType)
enum class EPDUType : uint8
{
	Other,
	EntityState,
	Fire,
	Detonation,
	Collision,
	ServiceRequest,
	ResupplyOffer,
	RessuplyReceived,
	ResupplyCancel,
	RepairComplete,
	RepairResponse,
	CreateEntity,
	RemoveEntity,
	Start_Resume,
	Stop_Freeze,
	Acknowledge,
	ActionRequest,
	ActionResponse,
	DataQuery,
	SetData,
	Data,
	EventReport,
	Comment,
	ElectromagneticEmission,
	Designator,
	Transmitter,
	Signal,
	Receiver,
	IFF,
	UnderwaterAcoustic,
	SupplementalEmission_EntityState,
	IntercomSignal,
	IntercomControl,
	AggregateState,
	IsGroupOf,
	TransferOwnership,
	IsPartOf,
	MinefieldState,
	MinefieldQuery,
	MinefieldData,
	MinefieldResponseNegativeAcknowledgement,
	EnvironmentalProcess,
	GriddedData,
	PointObjectState,
	LinearObjectState,
	ArealObjectState,
	TimeSpacePositionInformation,
	Appearance,
	ArticulatedParts,
	LEFire,
	LEDetonate,
	CreateEntity_R,
	RemoveEntity_R,
	Start_Resume_R,
	Stop_Freeze_R,
	Acknowledge_R,
	ActionRequest_R,
	ActionResponse_R,
	DataQuery_R,
	SetData_R,
	Data_R,
	EventReport_R,
	Comment_R_Message,
	Record_R,
	SetRecord_R,
	RecordQuery_R,
	Collision_Elastic,
	EntityStateUpdate,
	DirectedEnergyFire,
	EntityDamageStatus,
	InformationOperationsAction,
	InformationOperationsReport,
	Attribute
};

UENUM(BlueprintType)
enum class EReason : uint8
{
	Other,
	Recess,
	Termination,
	SystemFailure,
	SecurityViolation,
	EntityReconstruction,
	StopForReset,
	StopForRestart,
	AbortTrainingReturnToTacticalOperations
};

UENUM(BlueprintType)
enum class EDetonationResult : uint8
{
	Other								UMETA(DisplayName = "Other"),
	EntityImpact						UMETA(DisplayName = "Entity Impact"),
	EntityProximateDetonation			UMETA(DisplayName = "Entity Proximate Detonation"),
	GroundImpact						UMETA(DisplayName = "Ground Impact"),
	GroundProximateImpact				UMETA(DisplayName = "Ground Proximate Impact"),
	Detonation							UMETA(DisplayName = "Detonation"),
	Dud									UMETA(DisplayName = "None or No Detonation (Dud)"),
	HE_hit_sm							UMETA(DisplayName = "HE hit, small"),
	HE_hit_md							UMETA(DisplayName = "HE hit, medium"),
	HE_hit_lg							UMETA(DisplayName = "HE hit, large"),
	ArmorPiercingHit					UMETA(DisplayName = "Armor-piercing hit"),
	DirtBlast_sm						UMETA(DisplayName = "Dirt blast, small"),
	DirtBlast_md						UMETA(DisplayName = "Dirt blast, medium"),
	DirtBlast_lg						UMETA(DisplayName = "Dirt blast, large"),
	WaterBlast_sm						UMETA(DisplayName = "Water blast, small"),
	WaterBlast_md						UMETA(DisplayName = "Water blast, medium"),
	WaterBlast_lg						UMETA(DisplayName = "Water blast, large"),
	AirHit								UMETA(DisplayName = "Air hit"),
	BuildingHit_sm						UMETA(DisplayName = "Building hit, small"),
	BuildingHit_md						UMETA(DisplayName = "Building hit, medium"),
	BuildingHit_lg						UMETA(DisplayName = "Building hit, large"),
	MineClearingLineCharge				UMETA(DisplayName = "Mine-clearing line charge"),
	EnvironmentObjectImpact				UMETA(DisplayName = "Environment object impact"),
	EnvironmentObjectProximateImpact	UMETA(DisplayName = "Environment object proximate detonation"),
	WaterImpact							UMETA(DisplayName = "Water impact"),
	AirBurst							UMETA(DisplayName = "Air Burst"),
	KillWithFragmentType1				UMETA(DisplayName = "Kill with fragment type 1"),
	KillWithFragmentType2				UMETA(DisplayName = "Kill with fragment type 2"),
	KillWithFragmentType3				UMETA(DisplayName = "Kill with fragment type 3"),
	KillWithFragmentType1FlyOutFailure	UMETA(DisplayName = "Kill with fragment type 1 after fly-out failure"),
	KillWithFragmentType2FlyOutFailure	UMETA(DisplayName = "Kill with fragment type 2 after fly-out failure"),
	MissDueToFlyOutFailure				UMETA(DisplayName = "Miss due to fly-out failure"),
	MissDueToEndGameFailure				UMETA(DisplayName = "Miss due to end-game failure"),
	MissDueToFlyOutAndEndGameFailure	UMETA(DisplayName = "Miss due to fly-out and end-game failure")
};

UENUM(BlueprintType)
enum class EEntityDamage : uint8
{
	NoDamage,
	SlightDamage,
	ModerateDamage,
	Destroyed
};

UENUM(BlueprintType)
enum class EBeamFunction: uint8
{
	Other,
	Search,
	HeightFinding,
	Acquisition,
	Tracking,
	AcquisitionAndTracking,
	CommandGuidance,
	Illumination,
	Ranging,
	MissileBeacon,
	MissileFusing,
	ActiveRadarMissileSeeker,
	Jamming,
	IFF,
	NavigationWeather,
	Meteorological,
	DataTransmission,
	NavigationalDirectionalBeacon,
	TimeSharedSearch,
	TimeSharedAcquisition,
	TimeSharedTrack,
	TimeSharedCommandGuidance,
	TimeSharedIllumination,
	TimeSharedJamming,
};

UENUM(BlueprintType)
enum class EArtPartTypeMetric : uint8
{
	NotSpecified = 0,
	Position = 1,
	PositionRate = 2,
	Extension = 3,
	ExtensionRate = 4,
	X = 5,
	XRate = 6,
	Y = 7,
	YRate = 8,
	Z = 9,
	ZRate = 10,
	Azimuth = 11,
	AzimuthRate = 12,
	Elevation = 13,
	ElevationRate = 14,
	Rotation = 15,
	RotationRate = 16,
};

/*
* Since UE only supports uint8 Enums, we can only have the first 256 values.
* The DIS enum is defined as multiples of 32 in the range 1,024 - 4,294,967,264
* The formula from the DIS enum value is ((x - 1024) / 32) + 1 for the non zero values.
*/
UENUM(BlueprintType)
enum class EArtPartTypeClass : uint8
{
	NotSpecified = 0,
	Rudder = 1,
	LeftFlap = 2,
	RightFlap = 3,
	LeftAileron = 4,
	RightAileron = 5,
	HelicopterMainRotor = 6,
	HelicopterTailRotor = 7,
	OtherAircraftControlSurfacesDefinedasNeeded = 8,
	PropellerNumber1 = 9,
	PropellerNumber2 = 10,
	PropellerNumber3 = 11,
	PropellerNumber4 = 12,
	LeftStabilatorStabilatorNumber1 = 13,
	RightStabilatorStabilatorNumber2 = 14,
	LeftRuddervatorRuddervatorNumber1 = 15,
	RightRuddervatorRuddervatorNumber2 = 16,
	LeftLeadingEdgeFlapSlat = 17,
	RightLeadingEdgeFlapSlat = 18,
	LeftElevator = 19,
	RightElevator = 20,
	CanardLeft = 21,
	CanardRight = 22,
	ElevonInnerLeft = 23,
	ElevonInnerRight = 24,
	ElevonMiddleLeft = 25,
	ElevonMiddleRight = 26,
	ElevonOuterLeft = 27,
	ElevonOuterRight = 28,
	CanopyAircraft = 29,
	Periscope = 33,
	GenericAntenna = 34,
	Snorkel = 35,
	OtherExtendiblePartsDefinedasNeeded = 36,
	DivePlaneSailLeft = 37,
	DivePlaneSailRight = 38,
	DivePlaneBowLeft = 39,
	DivePlaneBowRight = 40,
	DivePlaneSternLeft = 41,
	DivePlaneSternRight = 42,
	LandingGear287 = 65,
	TailHook = 66,
	SpeedBrake = 67,
	LeftDoorofPrimaryWeaponBay = 68,
	RightDoorofPrimaryWeaponBay = 69,
	TankorAPCHatch = 70,
	Wingsweep = 71,
	BridgeLauncher = 72,
	BridgeSection1 = 73,
	BridgeSection2 = 74,
	BridgeSection3 = 75,
	PrimaryBlade1 = 76,
	PrimaryBlade2 = 77,
	PrimaryBoom = 78,
	PrimaryLauncherArm = 79,
	OtherFixedPositionPartsDefinedasNeeded = 80,
	LandingGearNose = 81,
	LandingGearLeftMain = 82,
	LandingGearRightMain = 83,
	DoorsofLeftSideWeaponBay = 84,
	DoorsofRightSideWeaponBay = 85,
	SpotSearchLight1 = 86,
	SpotSearchLight2 = 87,
	SpotSearchLight3 = 88,
	SpotSearchLight4 = 89,
	LandingLight = 90,
	PrimaryTurretNumber1 = 97,
	PrimaryTurretNumber2 = 98,
	PrimaryTurretNumber3 = 99,
	PrimaryTurretNumber4 = 100,
	PrimaryTurretNumber5 = 101,
	PrimaryTurretNumber6 = 102,
	PrimaryTurretNumber7 = 103,
	PrimaryTurretNumber8 = 104,
	PrimaryTurretNumber9 = 105,
	PrimaryTurretNumber10 = 106,
	PrimaryGunNumber1 = 107,
	PrimaryGunNumber2 = 108,
	PrimaryGunNumber3 = 109,
	PrimaryGunNumber4 = 110,
	PrimaryGunNumber5 = 111,
	PrimaryGunNumber6 = 112,
	PrimaryGunNumber7 = 113,
	PrimaryGunNumber8 = 114,
	PrimaryGunNumber9 = 115,
	PrimaryGunNumber10 = 116,
	PrimaryLauncher1 = 117,
	PrimaryLauncher2 = 118,
	PrimaryLauncher3 = 119,
	PrimaryLauncher4 = 120,
	PrimaryLauncher5 = 121,
	PrimaryLauncher6 = 122,
	PrimaryLauncher7 = 123,
	PrimaryLauncher8 = 124,
	PrimaryLauncher9 = 125,
	PrimaryLauncher10 = 126,
	PrimaryDefenseSystems1288 = 127,
	PrimaryDefenseSystems2 = 128,
	PrimaryDefenseSystems3 = 129,
	PrimaryDefenseSystems4 = 130,
	PrimaryDefenseSystems5 = 131,
	PrimaryDefenseSystems6 = 132,
	PrimaryDefenseSystems7 = 133,
	PrimaryDefenseSystems8 = 134,
	PrimaryDefenseSystems9 = 135,
	PrimaryDefenseSystems10 = 136,
	PrimaryRadar1289 = 137,
	PrimaryRadar2 = 138,
	PrimaryRadar3 = 139,
	PrimaryRadar4 = 140,
	PrimaryRadar5 = 141,
	PrimaryRadar6 = 142,
	PrimaryRadar7 = 143,
	PrimaryRadar8 = 144,
	PrimaryRadar9 = 145,
	PrimaryRadar10 = 146,
	SecondaryTurretNumber1 = 147,
	SecondaryTurretNumber2 = 148,
	SecondaryTurretNumber3 = 149,
	SecondaryTurretNumber4 = 150,
	SecondaryTurretNumber5 = 151,
	SecondaryTurretNumber6 = 152,
	SecondaryTurretNumber7 = 153,
	SecondaryTurretNumber8 = 154,
	SecondaryTurretNumber9 = 155,
	SecondaryTurretNumber10 = 156,
	SecondaryGunNumber1 = 157,
	SecondaryGunNumber2 = 158,
	SecondaryGunNumber3 = 159,
	SecondaryGunNumber4 = 160,
	SecondaryGunNumber5 = 161,
	SecondaryGunNumber6 = 162,
	SecondaryGunNumber7 = 163,
	SecondaryGunNumber8 = 164,
	SecondaryGunNumber9 = 165,
	SecondaryGunNumber10 = 166,
	SecondaryLauncher1 = 167,
	SecondaryLauncher2 = 168,
	SecondaryLauncher3 = 169,
	SecondaryLauncher4 = 170,
	SecondaryLauncher5 = 171,
	SecondaryLauncher6 = 172,
	SecondaryLauncher7 = 173,
	SecondaryLauncher8 = 174,
	SecondaryLauncher9 = 175,
	SecondaryLauncher10 = 176,
	SecondaryDefenseSystems1 = 177,
	SecondaryDefenseSystems2 = 178,
	SecondaryDefenseSystems3 = 179,
	SecondaryDefenseSystems4 = 180,
	SecondaryDefenseSystems5 = 181,
	SecondaryDefenseSystems6 = 182,
	SecondaryDefenseSystems7 = 183,
	SecondaryDefenseSystems8 = 184,
	SecondaryDefenseSystems9 = 185,
	SecondaryDefenseSystems10 = 186,
	SecondaryRadar1 = 187,
	SecondaryRadar2 = 188,
	SecondaryRadar3 = 189,
	SecondaryRadar4 = 190,
	SecondaryRadar5 = 191,
	SecondaryRadar6 = 192,
	SecondaryRadar7 = 193,
	SecondaryRadar8 = 194,
	SecondaryRadar9 = 195,
	SecondaryRadar10 = 196,
	DeckElevator1 = 197,
	DeckElevator2 = 198,
	Catapult1 = 199,
	Catapult2 = 200,
	JetBlastDeflector1 = 201,
	JetBlastDeflector2 = 202,
	ArrestorWires1 = 203,
	ArrestorWires2 = 204,
	ArrestorWires3 = 205,
	WingorRotorFold = 206,
	FuselageFold = 207,
	MainCargoDoor = 208,
	CargoRamp = 209,
	AirtoAirRefuelingBoom = 210,
	PrimaryAerialRefuelingReceptacleDoor = 211,
	SecondaryAerialRefuelingReceptacleDoor = 212,
	AerialRefuelingReceptacleLatch = 213,
	CargoDoor1 = 214,
	CargoDoor2 = 215,
	CargoDoor3 = 216,
	CargoDoor4 = 217,
	CargoDoor5 = 218,
	CargoDoor6 = 219,
	CargoDoor7 = 220,
	CargoDoor8 = 221,
	CargoDoor9 = 222,
	CargoDoor10 = 223,
	CentreRefuellingDrogue = 224,
	PortRefuellingDrogue = 225,
	StarboardRefuellingDrogue = 226,
	SubmarineEngineExhaustMast = 227,
	SubmarineMast1290 = 228,
	SubmarineMast2 = 229,
	SubmarineMast3 = 230,
	SubmarineMast4 = 231,
	SubmarineMast5 = 232,
	SubmarineMast6 = 233,
	SubmarineMast7 = 234,
	SubmarineMast8 = 235,
	SubmarineMast9 = 236,
	SubmarineMast10 = 237,
	VectoredThrustNozzle = 238,
	LeftDooroftheLeftWeaponBay = 239,
	RightDooroftheLeftWeaponBay = 240,
	LeftDooroftheRightWeaponBay = 241,
	RightDooroftheRightWeaponBay = 242,
	GunDoor = 243,
	CountermeasureDoorLeft = 244,
	CountermeasureDoorRight = 245,
	HookDoorForward = 246,
	HookDoorAft = 247,
	LiftFanUpperDoor = 248,
	LiftFanLowerDoorLeft = 249,
	LiftFanLowerDoorRight = 250,
	RefuelProbeDoor = 251,
	LeftEngineNacelle = 252,
	RightEngineNacelle = 253,
	LeftWheel1st = 254,
	RightWheel1st = 255,
};

USTRUCT(BlueprintType)
struct FEastNorthUp
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FVector EastVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FVector NorthVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FVector UpVector;

	FEastNorthUp()
	{
		NorthVector = FVector(0, 1, 0);
		EastVector = FVector(1, 0, 0);
		UpVector = FVector(0, 0, 1);
	}

	FEastNorthUp(FVector EastVector, FVector NorthVector, FVector UpVector)
	{
		this->EastVector = EastVector;
		this->NorthVector = NorthVector;
		this->UpVector = UpVector;
	}
};

USTRUCT(BlueprintType)
struct FNorthEastDown
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FVector NorthVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FVector EastVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FVector DownVector;

	FNorthEastDown()
	{
		NorthVector = FVector(0, 1, 0);
		EastVector = FVector(1, 0, 0);
		DownVector = FVector(0, 0, -1);
	}

	FNorthEastDown(FVector NorthVector, FVector EastVector, FVector DownVector)
	{
		this->NorthVector = NorthVector;
		this->EastVector = EastVector;
		this->DownVector = DownVector;
	}
};

USTRUCT(BlueprintType)
struct FHeadingPitchRoll
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		float Heading;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		float Pitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		float Roll;

	FHeadingPitchRoll()
	{
		Heading = 0.0f;
		Pitch = 0.0f;
		Roll = 0.0f;
	}

	FHeadingPitchRoll(const float Heading, const float Pitch, const float Roll)
	{
		this->Heading = Heading;
		this->Pitch = Pitch;
		this->Roll = Roll;
	}
};

USTRUCT(BlueprintType)
struct FPsiThetaPhi
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		float Psi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		float Theta;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		float Phi;

	FPsiThetaPhi()
	{
		Psi = 0.0f;
		Theta = 0.0f;
		Phi = 0.0f;
	}

	FPsiThetaPhi(const float Psi, const float Theta, const float Phi)
	{
		this->Psi = Psi;
		this->Theta = Theta;
		this->Phi = Phi;
	}

	FPsiThetaPhi(FRotator UnrealRotation)
	{
		this->Psi = UnrealRotation.Yaw;
		this->Theta = UnrealRotation.Pitch;
		this->Phi = UnrealRotation.Roll;
	}
};

USTRUCT(BlueprintType)
struct FClockTime
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		int32 Hour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "4294967295"), Category = "GRILL DIS|Structs")
		int64 TimePastHour;

	FClockTime()
	{
		Hour = 0;
		TimePastHour = 0;
	}

	DIS::ClockTime ToOpenDIS() const
	{
		DIS::ClockTime OutClockTime;

		OutClockTime.setHour(Hour);
		OutClockTime.setTimePastHour(TimePastHour);

		return OutClockTime;
	}
};

USTRUCT(BlueprintType)
struct FEntityID
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Site;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Application;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Entity;

	FEntityID()
	{
		Site = 0;
		Application = 0;
		Entity = 0;
	}

	FEntityID(DIS::EntityID EntityID)
	{
		this->Site = EntityID.getSite();
		this->Application = EntityID.getApplication();
		this->Entity = EntityID.getEntity();
	}

	bool operator== (const FEntityID other) const
	{
		return Site == other.Site
			&& Application == other.Application
			&& Entity == other.Entity;
	}

	bool operator!= (const FEntityID Other) const
	{
		return !(operator==(Other));
	}

	bool operator< (const FEntityID Other) const
	{
		return ToUInt64() < Other.ToUInt64();
	}

	bool operator> (const FEntityID Other) const
	{
		return Other.operator<(*this);
	}

	bool operator<= (const FEntityID Other) const
	{
		return !(operator>(Other));
	}

	bool operator>= (const FEntityID Other) const
	{
		return !(operator<(Other));
	}

	friend uint32 GetTypeHash(const FEntityID& other)
	{
		const FString EntityID = FString::Printf(TEXT("%d:%d:%d"),
			other.Site,
			other.Application,
			other.Entity
		);
		return GetTypeHash(EntityID);
	}

	FString ToString()
	{
		return FString::FromInt(Site) + ":" + FString::FromInt(Application) + ':' + FString::FromInt(Entity);
	}

	DIS::EntityID ToOpenDIS() const
	{
		DIS::EntityID OutID;
		OutID.setSite(Site);
		OutID.setApplication(Application);
		OutID.setEntity(Entity);
		return OutID;
	}

	uint64 ToUInt64() const
	{
		return (static_cast<uint64>(Site) << 32) | (static_cast<uint64>(Application) << 16) | (static_cast<uint64>(Entity));
	}
};

USTRUCT(BlueprintType)
struct FEventID
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Site;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Application;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 EventNumber;

	FEventID()
	{
		Site = 0;
		Application = 0;
		EventNumber = 0;
	}

	FEventID(DIS::EventID EventID)
	{
		this->Site = EventID.getSite();
		this->Application = EventID.getApplication();
		this->EventNumber = EventID.getEventNumber();
	}

	DIS::EventID ToOpenDIS() const
	{
		DIS::EventID OutID;
		OutID.setSite(Site);
		OutID.setApplication(Application);
		OutID.setEventNumber(EventNumber);
		return OutID;
	}
};

USTRUCT(BlueprintType)
struct FEntityType
{
	GENERATED_BODY()

		/** Kind of entity */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"), Category = "GRILL DIS|Structs")
		int32 EntityKind;
	/** Domain of entity (air, surface, subsurface, space, etc) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"), Category = "GRILL DIS|Structs")
		int32 Domain;
	/** Country to which the design of the entity is attributed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Country;
	/** The main category that describes the entity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"), Category = "GRILL DIS|Structs")
		int32 Category;
	/** The particular subcategory to which the entity belongs based on the `Category` field */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"), Category = "GRILL DIS|Structs")
		int32 Subcategory;
	/** Specific information about the entity based on `Subcategory` field */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"), Category = "GRILL DIS|Structs")
		int32 Specific;
	/** Extra information required to describe a particular entity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"), Category = "GRILL DIS|Structs")
		int32 Extra;

	FEntityType()
	{
		EntityKind = -1;
		Domain = -1;
		Country = -1;
		Category = -1;
		Subcategory = -1;
		Specific = -1;
		Extra = -1;
	}

	FEntityType(DIS::EntityType EntityType)
	{
		this->EntityKind = EntityType.getEntityKind();
		this->Domain = EntityType.getDomain();
		this->Country = EntityType.getCountry();
		this->Category = EntityType.getCategory();
		this->Subcategory = EntityType.getSubcategory();
		this->Specific = EntityType.getSpecific();
		this->Extra = EntityType.getExtra();
	}

	FEntityType(double EntityType)
	{
		uint8_t* EntityTypeInBytes = reinterpret_cast<uint8_t*>(&EntityType);

		if (sizeof(EntityTypeInBytes) != 8)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to convert double to Entity Type. Resorting to default values."));

			EntityKind = -1;
			Domain = -1;
			Country = -1;
			Category = -1;
			Subcategory = -1;
			Specific = -1;
			Extra = -1;

			return;
		}

		EntityKind = EntityTypeInBytes[7];
		Domain = EntityTypeInBytes[6];
		Country = ((uint16_t)EntityTypeInBytes[5] << 8) | EntityTypeInBytes[4];
		Category = EntityTypeInBytes[3];
		Subcategory = EntityTypeInBytes[2];
		Specific = EntityTypeInBytes[1];
		Extra = EntityTypeInBytes[0];
	}

	FEntityType FillWildcards(const FEntityType Other)
	{
		if (EntityKind == -1)
		{
			EntityKind = Other.EntityKind;
		}
		if (Domain == -1)
		{
			Domain = Other.Domain;
		}
		if (Country == -1)
		{
			Country = Other.Country;
		}
		if (Category == -1)
		{
			Category = Other.Category;
		}
		if (Subcategory == -1)
		{
			Subcategory = Other.Subcategory;
		}
		if (Specific == -1)
		{
			Specific = Other.Specific;
		}
		if (Extra == -1)
		{
			Extra = Other.Extra;
		}

		return FEntityType(*this);
	}

	bool operator== (const FEntityType& Other) const
	{
		return EntityKind == Other.EntityKind
			&& Domain == Other.Domain
			&& Country == Other.Country
			&& Category == Other.Category
			&& Subcategory == Other.Subcategory
			&& Specific == Other.Specific
			&& Extra == Other.Extra;
	}

	bool operator!= (const FEntityType& Other) const
	{
		return !(operator==(Other));
	}

	bool operator< (const FEntityType& Other) const
	{
		const bool bIsLessThan = ToUInt64() < Other.ToUInt64();
		return bIsLessThan;
	}

	bool operator> (const FEntityType& Other) const
	{
		return Other.operator<(*this);
	}

	bool operator<= (const FEntityType& Other) const
	{
		return !(operator>(Other));
	}

	bool operator>= (const FEntityType& Other) const
	{
		return !(operator<(Other));
	}

	friend uint32 GetTypeHash(const FEntityType& Other)
	{
		const FString EntityTypeString = FString::Printf(TEXT("%d.%d.%d.%d.%d.%d.%d"),
			Other.EntityKind,
			Other.Domain,
			Other.Country,
			Other.Category,
			Other.Subcategory,
			Other.Specific,
			Other.Extra
		);
		return GetTypeHash(EntityTypeString);
	}

	FString ToString() const
	{
		return FString::FromInt(EntityKind) + ":" + FString::FromInt(Domain) + ':' + FString::FromInt(Country) + ":" +
			FString::FromInt(Category) + ":" + FString::FromInt(Subcategory) + ':' + FString::FromInt(Specific) + ":" + FString::FromInt(Extra);
	}

	uint64 ToUInt64() const
	{
		const uint64 BitString = ((static_cast<uint64>(Extra) & 0xFF) << 0) | ((static_cast<uint64>(Specific) & 0xFF) << 8) | ((static_cast<uint64>(Subcategory) & 0xFF) << 16) |
			((static_cast<uint64>(Category) & 0xFF) << 24) | ((static_cast<uint64>(Country) & 0xFF) << 32) | ((static_cast<uint64>(Domain) & 0xFF) << 48) | ((static_cast<uint64>(EntityKind) & 0xFF) << 56);

		return BitString;
	}

	double ToDouble() const
	{
		uint8_t temp[8];
		temp[0] = Extra;
		temp[1] = Specific;
		temp[2] = Subcategory;
		temp[3] = Category;
		temp[4] = Country & 0xFF;
		temp[5] = Country >> 8;
		temp[6] = Domain;
		temp[7] = EntityKind;

		double EntityTypeAsDouble = reinterpret_cast<double&>(*temp);

		return EntityTypeAsDouble;
	}

	FString ToBitString() const
	{
		uint64 BitString = ToUInt64();
		return BytesToHex(reinterpret_cast<uint8*>(&BitString), 8);
	}

	DIS::EntityType ToOpenDIS() const
	{
		if (*this == FEntityType())
		{
			DIS::EntityType OutType;
			OutType.setEntityKind(0);
			OutType.setDomain(0);
			OutType.setCountry(0);
			OutType.setCategory(0);
			OutType.setSubcategory(0);
			OutType.setSpecific(0);
			OutType.setExtra(0);
			return OutType;
		}
		else
		{
			DIS::EntityType OutType;
			OutType.setEntityKind(EntityKind);
			OutType.setDomain(Domain);
			OutType.setCountry(Country);
			OutType.setCategory(Category);
			OutType.setSubcategory(Subcategory);
			OutType.setSpecific(Specific);
			OutType.setExtra(Extra);
			return OutType;
		}
	}
};

USTRUCT(BlueprintType)
struct FArticulationParameters
{
	GENERATED_BODY()

		/**  Identification of whether the Parameter Type Record is for an articulated (0) or attached part (1) shall be designated by this field */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "1"), Category = "GRILL DIS|Structs")
		int32 ParameterTypeDesignator;
	/** Indicates the change of any paramater for any articulated part. Increments by 1 for each change. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"), Category = "GRILL DIS|Structs")
		int32 ChangeIndicator;
	/** The ID of the part to which this part is attached */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 PartAttachedTo;
	/** The type class (multiples of 32 in the range 1,024 - 4,294,967,264) and type metric (0 - 31) of the articulated part. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		int32 ParameterType;
	/** The type class (multiples of 32 in the range 1,024 - 4,294,967,264) of the articulated part. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		EArtPartTypeClass ParameterTypeClass;
	/** The type metric (0 - 31) of the articulated part. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		EArtPartTypeMetric ParameterTypeMetric;
	/** The parameter value as defined by the ParameterType variable. Will only be utilized if the Parameter Type Designator is an articulated part (0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		float ParameterValue;
	/** The type of the entity. Will only be utilized if the Parameter Type Designator is an attached part (1). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FEntityType AttachedPartType;

	FArticulationParameters()
	{
		ParameterTypeDesignator = 0;
		ChangeIndicator = 0;
		PartAttachedTo = 0;
		ParameterType = 0;
		ParameterTypeClass = EArtPartTypeClass::NotSpecified;
		ParameterTypeMetric = EArtPartTypeMetric::NotSpecified;
		ParameterValue = 0.f;
	}

	DIS::ArticulationParameter ToOpenDIS() const
	{
		DIS::ArticulationParameter OutParam;
		OutParam.setParameterTypeDesignator(ParameterTypeDesignator);
		OutParam.setChangeIndicator(ChangeIndicator);
		OutParam.setPartAttachedTo(PartAttachedTo);
		OutParam.setParameterType(ParameterType);

		if (ParameterTypeDesignator == 0)
		{
			OutParam.setParameterValue(ParameterValue);
		}
		else
		{
			OutParam.setParameterValue(AttachedPartType.ToDouble());
		}

		return OutParam;
	}
	// From the spec DIS IEEE Std 1278.1-199
	//
	//An articulated parameter type consists of two components (figure A.1). The first component, consisting of
	//the least significant 5 bits of the Parameter Type field, defines the type metric. The type metric determines
	//which of the transformations described in A.2.1.4 are specified by this parameter type. The second component,
	//consisting of the next 27 bits of the Parameter Type field, defines the type class.
    static EArtPartTypeMetric getParameterTypeMetric(int ParameterType) {
        return static_cast<EArtPartTypeMetric>(ParameterType & 0x1f);
    }

    static EArtPartTypeClass getParameterTypeClass(int ParameterType) {
        return ParameterType == 0 
			? EArtPartTypeClass::NotSpecified 
			: static_cast<EArtPartTypeClass>((((ParameterType >> 5) - 1024)/32)+1);
    }
};

USTRUCT(BlueprintType)
struct FBurstDescriptor
{
	GENERATED_BODY()

		/** The type of the entity */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FEntityType EntityType;
	/** The type of warhead (0 - 65,535) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Warhead;
	/** The type of fuse (0 - 65,535) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Fuse;
	/** The number of bursts represented (0 - 65,535) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Quantity;
	/** The number of rounds per minute for the munition (0 - 65,535) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "65535"), Category = "GRILL DIS|Structs")
		int32 Rate;

	FBurstDescriptor()
	{
		Warhead = 0;
		Fuse = 0;
		Quantity = 0;
		Rate = 0;
	}

	DIS::BurstDescriptor ToOpenDIS() const
	{
		DIS::BurstDescriptor OutDescriptor;
		OutDescriptor.setMunition(EntityType.ToOpenDIS());
		OutDescriptor.setWarhead(Warhead);
		OutDescriptor.setFuse(Fuse);
		OutDescriptor.setQuantity(Quantity);
		OutDescriptor.setRate(Rate);
		return OutDescriptor;
	}
};

USTRUCT(BlueprintType)
struct FDeadReckoningParameters
{
	GENERATED_BODY()

		/** The type of dead reackoning algorithm used by the entity (0 - 9) */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "9"), Category = "GRILL DIS|Structs")
		EDeadReckoningAlgorithm DeadReckoningAlgorithm;
	/** Field used to specify other dead reckoning parameters which are currently undefined */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		TArray<uint8> OtherParameters;
	/** The entity's linear acceleration in m/s^2 in either the World Coordinate System or the Entity's Coordinate System depending on the `DeadReckoningAlgorithm` field. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FVector EntityLinearAcceleration;
	/** The entity's angular acceleration in radians per second about each of the entity's own coordinate axes. Positive acceleration is defined by the right hand rule. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		FVector EntityAngularVelocity;

	FDeadReckoningParameters()
	{
		DeadReckoningAlgorithm = EDeadReckoningAlgorithm::Static;
		OtherParameters.Init(0, 15);
		EntityLinearAcceleration = FVector(0, 0, 0);
		EntityAngularVelocity = FVector(0, 0, 0);
	}

	DIS::DeadReckoningParameter ToOpenDIS() const
	{
		DIS::DeadReckoningParameter OutParam;
		OutParam.setDeadReckoningAlgorithm((uint8)DeadReckoningAlgorithm);
		OutParam.setOtherParameters(reinterpret_cast<const char*>(OtherParameters.GetData()));
		DIS::Vector3Float OutLinearAcceleration;
		OutLinearAcceleration.setX(EntityLinearAcceleration.X);
		OutLinearAcceleration.setY(EntityLinearAcceleration.Y);
		OutLinearAcceleration.setZ(EntityLinearAcceleration.Z);
		OutParam.setEntityLinearAcceleration(OutLinearAcceleration);
		DIS::Vector3Float OutAngularVelocity;
		OutAngularVelocity.setX(EntityAngularVelocity.X);
		OutAngularVelocity.setY(EntityAngularVelocity.Y);
		OutAngularVelocity.setZ(EntityAngularVelocity.Z);
		OutParam.setEntityAngularVelocity(OutAngularVelocity);
		return OutParam;
	}
};

USTRUCT(BlueprintType)
struct FEntityAppearance
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool PaintScheme = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool MobilityKilled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool FirePowerKilled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		EEntityDamage Damage = EEntityDamage::NoDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool IsSmoking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool IsEngineSmoking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		int Trailing = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		int HatchState = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool LightPrimary = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool LightSecondary = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool LightCollision = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool IsFlaming = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool IsFrozen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool IsDeactivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GRILL DIS|Structs")
		bool IsLandingGearExtended = false;

	int32 RawVal = 0;

	FEntityAppearance() {}

	FEntityAppearance(uint32 val)
		: RawVal(val)
	{
		PaintScheme = getField(val, 0);
		MobilityKilled = getField(val, 1);
		FirePowerKilled = getField(val, 2);
		Damage = static_cast<EEntityDamage>(getField(val, 0b11, 3));
		IsSmoking = getField(val, 5);
		IsEngineSmoking = getField(val, 6);
		Trailing = getField(val, 0b11, 7);
		HatchState = getField(val, 0b111, 9);
		LightPrimary = getField(val, 12);
		LightSecondary = getField(val, 13);
		LightCollision = getField(val, 14);
		IsFlaming = getField(val, 15);

		IsFrozen = getField(val, 21);
		IsDeactivated = getField(val, 23);

		IsLandingGearExtended = getField(val, 25);
	}

	static int getField(uint32 val, int mask, int pos)
	{
		return (val & (mask << pos)) >> pos;
	}
	static bool getField(uint32 val, int pos)
	{
		return getField(val, 0b1, pos) != 0;
	}

	int32 UpdateValue()
	{
		RawVal |= PaintScheme << 0;
		RawVal |= MobilityKilled << 1;
		RawVal |= FirePowerKilled << 2;
		RawVal |= int(Damage) << 3;
		RawVal |= IsSmoking << 5;
		RawVal |= IsEngineSmoking << 6;
		RawVal |= Trailing << 7;
		RawVal |= HatchState << 9;
		RawVal |= LightPrimary << 12;
		RawVal |= LightSecondary << 13;
		RawVal |= LightCollision << 14;
		RawVal |= IsFlaming << 15;
		RawVal |= IsFrozen << 21;
		RawVal |= IsDeactivated << 23;
		RawVal |= IsLandingGearExtended << 25;
		return RawVal;
	}
};