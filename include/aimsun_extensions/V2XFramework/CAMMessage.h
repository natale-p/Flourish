#pragma once

#include "V2XFrameworkUtil.h"

#include "V2XMessage.h"
#include <QVector>

struct ReferencePosition {
	double x;
	double y;
	double z;
};


struct PathPoint{
	ReferencePosition pathPosition;
	double pathDeltaTime;
};



struct ExteriorLights {
	bool lowBeamHeadlightsOn;  // Bit 0.
	bool highBeamHeadlightsOn;  // Bit 1.
	bool leftTurnSignalOn;  // Bit 2.
	bool rightTurnSignalOn;  // Bit 3.
	bool daytimeRunningLightsOn;  // Bit 4.
	bool reverseLightOn;  // Bit 5.
	bool fogLightOn;  // Bit 6.
	bool parkingLightsOn;  // Bit 7.
};


class AccelerationControl
{
public:
	AccelerationControl();
	virtual ~AccelerationControl();

	bool brakePedalEngaged;
	bool gasPedalEngaged;
	bool emergencyBrakeEngaged;
	bool collisionWarningEngaged;
	bool accEngaged;
	bool cruiseControlEngaged;
	bool speedLimiterEngaged;

	virtual void print() const;

};



class CenDsrcTollingZone
{
public:
	CenDsrcTollingZone();
	virtual ~CenDsrcTollingZone();

	ReferencePosition protectedZonePosition;
	int ProtectedZoneID;
	int cenDsrcTollingZoneID;
};



class PtActivation {
public:
	enum PtActivationType{ eUndefinedCodingType = 0, eR09_16CodingType = 1, eVdv_50149CodingType = 2};

	PtActivation();
	virtual ~PtActivation();

	PtActivationType getPtActivationType() const;
	QString &getPtActivationData();

	void setPtActivationType(int avalue);
private:
	PtActivationType ptActivationType;
	QString ptActivationData;
};


class PublicTransportContainer {
public:
	PublicTransportContainer();
	virtual ~PublicTransportContainer();

	PtActivation &getPtActivation();
	bool isEmbarkationStatus() const;
	void setEmbarkationStatus(bool avalue);

private:
	bool embarkationStatus;
	PtActivation ptActivation;
};


class PathHistory
{
public:

	PathHistory();
	virtual ~PathHistory();

	QVector<PathPoint> &getPathPoint();

private:
	QVector< PathPoint > pathPoint;
};


class V2XFRAMEWORKEXPORT BasicVehicleContainerLowFrequency
{
public:
	enum VehicleRole {eDefault =0, ePublicTransport=1,  eSpecialTransport=2, eDangerousGoods=3, eRoadWork=4, eRescue = 5, eEmergency = 6, eSafetyCar = 7, eAgriculture=8, eCommercial=9, eMilitary=10, eRoadOperator=11, eTaxi=12, eReserved1 = 13, eReserved2 = 14, eReserved3 = 15};

	BasicVehicleContainerLowFrequency();
	virtual ~BasicVehicleContainerLowFrequency();

	VehicleRole getVehicleRole() const;
	ExteriorLights &getExteriorLights();
	PathHistory &getPathHistory();

	void setVehicleRole(int avalue);

private:
	VehicleRole vehicleRole;
	ExteriorLights exteriorLights;
	PathHistory pathHistory;
};



class V2XFRAMEWORKEXPORT ProtectedCommunicationZone
{
	enum ProtectedZoneType {eCenDsrcTolling = 0};
public:

	ProtectedCommunicationZone();
	virtual ~ProtectedCommunicationZone();

	ProtectedZoneType getProtectedZoneType() const;
	void setProtectedZoneType(ProtectedZoneType avalue);

	double getExpiryTime() const;
	void setExpiryTime(double avalue);

	ReferencePosition &getProtectedZonePosition();
	void setProtectedZonePosition(ReferencePosition avalue);

	double getProtectedZoneRadius() const;
	void setProtectedZoneRadius(double avalue);

	int getProtectedZoneID() const;
	void setProtectedZoneIDs(int avalue);

private:
	ProtectedZoneType protectedZoneType;
	double expiryTime;
	ReferencePosition protectedZonePosition;
	double protectedZoneRadius;
	int protectedZoneID;
};


class RSUContainerHighFrequency
{
public:

	RSUContainerHighFrequency();
	virtual ~RSUContainerHighFrequency();

	QVector<ProtectedCommunicationZone> &getProtectedCommunicationZonesRSU();

private:
	QVector< ProtectedCommunicationZone > protectedCommunicationZonesRSU;

};


class V2XFRAMEWORKEXPORT BasicVehicleContainerHighFrequency
{
public:
	enum Heading {eWgs84North = 0, eWgs84East = 900, eWgs84South = 1800, eWgs84West = 2700, eNAHead = 3601};
	enum DriveDirection {eForward = 0, eBackward = 1, eNADD = 2};
	enum CurvatureCalculationMode {eYawRateUsed = 0, eYawRateNotUsed = 1, eNACurvC = 2};
	enum PerformanceClass {eNAPer = 0, ePerformanceClassA = 1, ePerformanceClassB = 2};


	BasicVehicleContainerHighFrequency();
	virtual ~BasicVehicleContainerHighFrequency();

	Heading getHeading() const;
	double getSpeed() const;
	DriveDirection getDriveDirection() const;
	double getVehicleLength() const;
	double getVehicleWidth() const;
	double getLongitudinalAcceleration() const;
	double getCurvature() const;
	CurvatureCalculationMode getCurvatureCalculationMode() const;
	double getYawRate() const;
	const AccelerationControl &getAccelerationControl() const;
	int getLanePosition() const;
	double getSteeringWheelAngle() const;
	double getLateralAcceleration() const;
	double getVerticalAcceleration() const;
	PerformanceClass getPerformanceClass() const;
	CenDsrcTollingZone &getCenDsrcTollingZone();

	void setHeading(Heading avalue);
	void setSpeed(double avalue);
	void setDriveDirection(DriveDirection avalue);
	void setVehicleLength(double avalue);
	void setVehicleWidth(double avalue);
	void setLongitudinalAcceleration(double avalue);
	void setCurvature(double avalue);
	void setCurvatureCalculationMode(CurvatureCalculationMode avalue);
	void setYawRate(double avalue);
	void setAccelerationControl(AccelerationControl avalue);
	void setLanePosition(int avalue);
	void setSteeringWheelAngle(double avalue);
	void setLateralAcceleration(double avalue);
	void setVerticalAcceleration(double avalue);
	void setPerformanceClass(PerformanceClass avalue);
	void setCenDsrcTollingZone(CenDsrcTollingZone avalue);


private:
	Heading heading;
	double speed;
	DriveDirection driveDirection;
	double vehicleLength;
	double vehicleWidth;
	double longitudinalAcceleration;
	double curvature;
	CurvatureCalculationMode curvatureCalculationMode;
	double  yawRate;
	AccelerationControl accelerationControl;
	int lanePosition;
	double steeringWheelAngle;
	double lateralAcceleration;
	double verticalAcceleration;
	PerformanceClass performanceClass;
	CenDsrcTollingZone cenDsrcTollingZone;
};


class V2XFRAMEWORKEXPORT SpecialVehicleContainer
{
public:

	SpecialVehicleContainer();
	virtual ~SpecialVehicleContainer();

	PublicTransportContainer &getPublicTransportContainer();
//	SpecialTransportContainer &getSpecialTransportContainer() const;
//	DangerousGoodsContainer &getDangerousGoodsContainer() const;
//	RoadWorksContainerBasic &getRoadWorksContainerBasic() const;
//	RescueContainer &getRescueContainer() const;
//	EmergencyContainer &getEmergencyContainer() const;
//	SafetyCarContainer &getSafetyCarContainer() const;

private:
	PublicTransportContainer publicTransportContainer;
//	SpecialTransportContainer specialTransportContainer;
//	DangerousGoodsContainer dangerousGoodsContainer;
//	RoadWorksContainerBasic roadWorksContainerBasic;
//	RescueContainer rescueContainer;
//	EmergencyContainer emergencyContainer;
//	SafetyCarContainer safetyCarContainer;
};


class V2XFRAMEWORKEXPORT LowFrequencyContainer
{
public:

	LowFrequencyContainer();
	virtual ~LowFrequencyContainer();

	BasicVehicleContainerLowFrequency &getBasicVehicleContainerLowFrequency();

private:
	BasicVehicleContainerLowFrequency basicVehicleContainerLowFrequency;

};


class V2XFRAMEWORKEXPORT HighFrequencyContainer
{
public:

	HighFrequencyContainer();
	virtual ~HighFrequencyContainer();

	BasicVehicleContainerHighFrequency &getBasicVehicleContainerHighFrequency();
	RSUContainerHighFrequency &getRSUContainerHighFrequency();
	bool hasBasicVehicleContainerHighFrequency() const;

private:
	BasicVehicleContainerHighFrequency basicVehicleContainerHighFrequency;
	RSUContainerHighFrequency rsuContainerHighFrequency;

};


class V2XFRAMEWORKEXPORT BasicContainer
{
public:
	enum StationType { eUnknown = 0, ePedestrian = 1, eCyclist = 2, eMoped = 3, eMotorcycle = 4, ePassengerCar = 5, eBus = 6, eLightTruck = 7, eHeavyTruck = 8, eTrailer = 9, eSpecialVehicles = 10, eTram = 11, eRoadSideUnit = 15};

	BasicContainer();
	virtual ~BasicContainer();

	StationType getStationType() const;
	ReferencePosition &getReferencePosition();

	void  setStationType(int avalue);
	void  setReferencePosition( const ReferencePosition &aref);

	virtual void print() const;


private:
	StationType stationType;
	ReferencePosition referencePosition;

};


class V2XFRAMEWORKEXPORT CamParameters
{
public:

	CamParameters();
	virtual ~CamParameters();

	BasicContainer &getBasicContainer();
	HighFrequencyContainer &getHighFrequencyContainer();
	LowFrequencyContainer &getLowFrequencyContainer();
	SpecialVehicleContainer &getSpecialVehicleContainer();

	virtual void print() const;


private:
	BasicContainer basicContainer;
	HighFrequencyContainer highFrequencyContainer;
	LowFrequencyContainer lowFrequencyContainer;
	SpecialVehicleContainer specialVehicleContainer;
};

class V2XFRAMEWORKEXPORT CoopAwareness
{
public:
	CoopAwareness();
	virtual ~CoopAwareness();

	double getGenerationDeltaTime() const;
	void setGenerationDeltaTime( double avalue);
	CamParameters &getCamParameters();
	virtual void print() const;

private:
	double generationDeltaTime;
	CamParameters camParameters;

};


class V2XFRAMEWORKEXPORT ItsPduHeader
{
public:
	enum MessageId { eNone = 0, eDemm = 1, eCam = 2};

	ItsPduHeader();
	virtual ~ItsPduHeader();

	int getProtocolVersion() const;
	MessageId getMessageId() const;
	int getStationId() const;

	void setProtocolVersion(int avalue);
	void setMessageId(int avalue);
	void setStationId(int avalue);

	virtual void print() const;

private:
	int protocolVersion;
	MessageId messageID;
	int stationID;

};



class V2XFRAMEWORKEXPORT CAMMessage: public V2XMessage
{
public:
	CAMMessage();
	virtual ~CAMMessage();
	virtual V2XMessage *copy() const;
	virtual void print() const;


	ItsPduHeader &getItsPduHeader();
	CoopAwareness &getCoopAwareness();

private:
	ItsPduHeader header;
	CoopAwareness cam;

};
