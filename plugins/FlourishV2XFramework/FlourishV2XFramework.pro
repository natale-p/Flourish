SUB_PROJECT_NAME = FlourishV2XFramework
BASE_DIR = ../../../..
include (../../config.incl)

SOURCES += \
	FlourishConnectedAgent.cpp \
	FlourishV2XFramework.cpp \
	FlourishVehicleRulesEngine.cpp \
	FlourishBroker.cpp \
	FlourishAP.cpp \
	FlourishInfrastructureRulesEngine.cpp

HEADERS += \
	FlourishV2XFrameworkUtil.h \
	FlourishConnectedAgent.h \
	FlourishV2XFramework.h \
	FlourishVehicleRulesEngine.h \
	FlourishBroker.h \
	FlourishAP.h \
	FlourishInfrastructureRulesEngine.h

macx {
	TARGET = $${BIN_PATH}/Aimsun.app/Contents/PlugIns/dynamicAPIS/FlourishV2XFramework
	QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/
}else{
	TARGET = $${BIN_PATH}/plugins/dynamicAPIS/FlourishV2XFramework
}

#-------------------------------------------------------------------------------------

TEMPLATE = lib
VERSION = 8.2.0

CONFIG += dll qt thread exceptions rtti

win32 {
	DEFINES += _V2XFrameworkEXTDLL_DEF
	DEFINES += _FlourishV2XFrameworkEXTDLL_DEF
}

QT += sql xml widgets

contains(DEVELOPER, true) {
	message("Developer build; install headers enabled")

	random_headers.path = ../../include/core/random
	random_headers.files += $${SOURCES_DIR}/core/random/FRand.h

	INSTALLS += random_headers
	PRE_TARGETDEPS += install_random_headers

	adynamic_api_headers.path = ../../include/core/ANG_DTA/ADynamicAPI
	adynamic_api_headers.files += $${SOURCES_DIR}/core/ANG_DTA/ADynamicAPI/ADynamicAgent.h
	adynamic_api_headers.files += $${SOURCES_DIR}/core/ANG_DTA/ADynamicAPI/ADynamicAPI.h
	adynamic_api_headers.files += $${SOURCES_DIR}/core/ANG_DTA/ADynamicAPI/ADynamicAPIUtil.h
	adynamic_api_headers.files += $${SOURCES_DIR}/core/ANG_DTA/ADynamicAPI/ADynamicAPISetup.h
	adynamic_api_headers.files += $${SOURCES_DIR}/core/ANG_DTA/ADynamicAPI/ADynamicControl.h

	INSTALLS += adynamic_api_headers
	PRE_TARGETDEPS += install_adynamic_api_headers

	V2XFramework_headers = \
	Asn1cContainer.h \
	CAMMessage.h \
	Channel.h \
	V2XConnectedAgent.h \
	V2XSimpleAP.h \
	DENMMessage.h \
	ErrorModel.h \
	NetDevice.h \
	Packet.h \
	SimpleChannel.h \
	SimpleNetDevice.h \
	SPATEMMessage.h \
	V2XFramework.h \
	V2XFrameworkUtil.h \
	V2XMessage.h \
	V2XRulesEngine.h \
	V2XNetworkNode.h \
	V2XIntersection.h \
	V2XGenericLane.h \
	MAPEMMessage.h

	v2x_framework_headers.path = ../../include/aimsun_extensions/V2XFramework
	for (header, V2XFramework_headers) {
		v2x_framework_headers.files += $${SOURCES_DIR}/aimsun_extensions/V2XFramework/$$header
	}

	INSTALLS += v2x_framework_headers
	PRE_TARGETDEPS += install_v2x_framework_headers

	ASN_headers = ANY.h \
	asn_application.h \
	asn_codecs.h \
	asn_codecs_prim.h \
	asn_internal.h \
	asn_SEQUENCE_OF.h \
	asn_SET_OF.h \
	asn_system.h \
	ber_decoder.h \
	ber_tlv_length.h \
	ber_tlv_tag.h \
	BIT_STRING.h \
	BMPString.h \
	BOOLEAN.h \
	constraints.h \
	constr_CHOICE.h \
	constr_SEQUENCE.h \
	constr_SEQUENCE_OF.h \
	constr_SET.h \
	constr_SET_OF.h \
	constr_TYPE.h \
	der_encoder.h \
	ENUMERATED.h \
	GeneralizedTime.h \
	GeneralString.h \
	GraphicString.h \
	IA5String.h \
	INTEGER.h \
	ISO646String.h \
	NativeEnumerated.h \
	NativeInteger.h \
	NativeReal.h \
	NULL.h \
	NumericString.h \
	ObjectDescriptor.h \
	OBJECT_IDENTIFIER.h \
	OCTET_STRING.h \
	per_decoder.h \
	per_encoder.h \
	per_opentype.h \
	per_support.h \
	PrintableString.h \
	REAL.h \
	RELATIVE-OID.h \
	T61String.h \
	TeletexString.h \
	UniversalString.h \
	UTCTime.h \
	UTF8String.h \
	VideotexString.h \
	VisibleString.h \
	xer_decoder.h \
	xer_encoder.h \
	xer_support.h

	asn1_headers.path = ../../include/aimsun_extensions/V2XFramework/ASN1
	for (header, ASN_headers) {
		asn1_headers.files += $${SOURCES_DIR}/aimsun_extensions/V2XFramework/ASN1/$$header
	}

	INSTALLS += asn1_headers
	PRE_TARGETDEPS += install_asn1_headers

	ITS-spec_headers = AbsolutePosition.h \
	AbsolutePositionWAltitude.h \
	AccelerationConfidence.h \
	AccelerationControl.h \
	AccidentSubCauseCode.h \
	ActionID.h \
	AdverseWeatherCondition-AdhesionSubCauseCode.h \
	AdverseWeatherCondition-ExtremeWeatherConditionSubCauseCode.h \
	AdverseWeatherCondition-PrecipitationSubCauseCode.h \
	AdverseWeatherCondition-VisibilitySubCauseCode.h \
	AdvisorySpeed.h \
	AdvisorySpeedList.h \
	AdvisorySpeedType.h \
	AlacarteContainer.h \
	AllowedManeuvers.h \
	AltitudeConfidence.h \
	Altitude.h \
	AltitudeValue.h \
	Angle.h \
	AnyCatalogue.h \
	ApproachID.h \
	AttributeIdList.h \
	AttributeList.h \
	Attributes.h \
	AxleWeightLimits.h \
	BasicContainer.h \
	BasicVehicleContainerHighFrequency.h \
	BasicVehicleContainerLowFrequency.h \
	BasicVehicleRole.h \
	CAM.h \
	CamParameters.h \
	CauseCode.h \
	CauseCodeType.h \
	CenDsrcTollingZone.h \
	CenDsrcTollingZoneID.h \
	ClosedLanes.h \
	CollisionRiskSubCauseCode.h \
	ComparisonOperator.h \
	CompleteVehicleCharacteristics.h \
	ComputedLane.h \
	ComputedSegment.h \
	ConnectingLane.h \
	Connection.h \
	ConnectionManeuverAssist-addGrpC.h \
	ConnectionManeuverAssist.h \
	ConnectionTrajectory-addGrpC.h \
	ConnectsToList.h \
	Control-addGrpC.h \
	CoopAwareness.h \
	CopValue.h \
	CountryCode.h \
	CS5.h \
	CurvatureCalculationMode.h \
	CurvatureConfidence.h \
	Curvature.h \
	CurvatureValue.h \
	DangerousEndOfQueueSubCauseCode.h \
	DangerousGoodsBasic.h \
	DangerousGoodsContainer.h \
	DangerousGoodsExtended.h \
	DangerousSituationSubCauseCode.h \
	DataParameters.h \
	DayOfWeek.h \
	DBV.h \
	DDD-DEP.h \
	DDD-DER.h \
	DDD.h \
	DDD-IO.h \
	DecentralizedEnvironmentalNotificationMessage.h \
	DeltaAltitude.h \
	DeltaAngle.h \
	DeltaLatitude.h \
	DeltaLongitude.h \
	DeltaPosition.h \
	DeltaReferencePosition.h \
	DeltaTime.h \
	DENM.h \
	DescriptiveName.h \
	DestinationPlace.h \
	DestinationRoad.h \
	DFL.h \
	DieselEmissionValues.h \
	Direction.h \
	Distance.h \
	DistanceOrDuration.h \
	DriveDirection.h \
	DrivenLineOffsetLg.h \
	DrivenLineOffsetSm.h \
	DriverCharacteristics.h \
	DrivingLaneStatus.h \
	DSecond.h \
	DSRCmsgID.h \
	DTM.h \
	EDT.h \
	Elevation.h \
	EmbarkationStatus.h \
	EmergencyContainer.h \
	EmergencyPriority.h \
	EmergencyVehicleApproachingSubCauseCode.h \
	EmissionType.h \
	EnabledLaneList.h \
	EnergyStorageType.h \
	EngineCharacteristics.h \
	EnvironmentalCharacteristics.h \
	EuroValue.h \
	EuVehicleCategoryCode.h \
	EuVehicleCategoryL.h \
	EuVehicleCategoryM.h \
	EuVehicleCategoryN.h \
	EuVehicleCategoryO.h \
	EventHistory.h \
	EventPoint.h \
	ExhaustEmissionValues.h \
	Ext1.h \
	Ext2.h \
	Ext3.h \
	ExteriorLights.h \
	GeneralIviContainer.h \
	GenerationDeltaTime.h \
	GenericLane.h \
	GeographicLocationContainer.h \
	GicPart.h \
	GlcPart.h \
	GoodsType.h \
	HardShoulderStatus.h \
	HazardousLocation-AnimalOnTheRoadSubCauseCode.h \
	HazardousLocation-DangerousCurveSubCauseCode.h \
	HazardousLocation-ObstacleOnTheRoadSubCauseCode.h \
	HazardousLocation-SurfaceConditionSubCauseCode.h \
	HeadingConfidence.h \
	Heading.h \
	HeadingValue.h \
	HeightLonCarr.h \
	HighFrequencyContainer.h \
	HoursMinutes.h \
	HumanPresenceOnTheRoadSubCauseCode.h \
	HumanProblemSubCauseCode.h \
	ImpactReductionContainer.h \
	InformationQuality.h \
	Int1.h \
	Int2.h \
	IntersectionAccessPoint.h \
	IntersectionGeometry.h \
	IntersectionGeometryList.h \
	IntersectionID.h \
	IntersectionReferenceID.h \
	IntersectionState-addGrpC.h \
	IntersectionState.h \
	IntersectionStateList.h \
	IntersectionStatusObject.h \
	ISO14823Attributes.h \
	ISO14823Code.h \
	Iso3833VehicleType.h \
	IssuerIdentifier.h \
	ItineraryPath.h \
	ItsPduHeader.h \
	ItsStationPosition.h \
	ItsStationPositionList.h \
	IviContainer.h \
	IVI.h \
	IviIdentificationNumber.h \
	IVILaneWidth.h \
	IVIManagementContainer.h \
	IVIM.h \
	IviPurpose.h \
	IviStatus.h \
	IviStructure.h \
	IviType.h \
	LaneAttributes-Barrier.h \
	LaneAttributes-Bike.h \
	LaneAttributes-Crosswalk.h \
	LaneAttributes.h \
	LaneAttributes-Parking.h \
	LaneAttributes-Sidewalk.h \
	LaneAttributes-Striping.h \
	LaneAttributes-TrackedVehicle.h \
	LaneAttributes-Vehicle.h \
	LaneConnectionID.h \
	LaneDataAttribute.h \
	LaneDataAttributeList.h \
	LaneDirection.h \
	LaneID.h \
	LaneInformation.h \
	LaneList.h \
	LanePosition.h \
	LaneSharing.h \
	LaneStatus.h \
	LaneTypeAttributes.h \
	LaneType.h \
	LaneWidth.h \
	LateralAcceleration.h \
	LateralAccelerationValue.h \
	Latitude.h \
	LayerID.h \
	LayerType.h \
	LayoutComponent.h \
	LayoutContainer.h \
	LightBarSirenInUse.h \
	LoadType.h \
	LocationContainer.h \
	Longitude.h \
	LongitudinalAcceleration.h \
	LongitudinalAccelerationValue.h \
	LowFrequencyContainer.h \
	ManagementContainer.h \
	ManeuverAssistList.h \
	MapData-addGrpC.h \
	MapData.h \
	MAPEM.h \
	MergeDivergeNodeAngle.h \
	MessageFrame.h \
	MinuteOfTheYear.h \
	MonthDay.h \
	MovementEvent.h \
	MovementEventList.h \
	MovementList.h \
	MovementPhaseState.h \
	MovementState.h \
	MsgCount.h \
	NodeAttributeSetXY.h \
	NodeAttributeXY.h \
	NodeAttributeXYList.h \
	NodeListXY.h \
	Node-LLmD-64b.h \
	NodeOffsetPointXY.h \
	NodeSetXY.h \
	Node-XY-20b.h \
	Node-XY-22b.h \
	Node-XY-24b.h \
	Node-XY-26b.h \
	Node-XY-28b.h \
	Node-XY-32b.h \
	NodeXY.h \
	NumberOfOccupants.h \
	Offset-B10.h \
	Offset-B11.h \
	Offset-B12.h \
	Offset-B13.h \
	Offset-B14.h \
	Offset-B16.h \
	OverlayLaneList.h \
	PassengerCapacity.h \
	PathDeltaTime.h \
	PathHistory.h \
	PathPoint.h \
	PedestrianBicycleDetect.h \
	PerformanceClass.h \
	PMD.h \
	PolygonalLine.h \
	PosCentMass.h \
	PosConfidenceEllipse.h \
	PosFrontAx.h \
	Position3D-addGrpC.h \
	Position3D.h \
	PositioningSolutionType.h \
	PositionOfOccupants.h \
	PositionOfPillars.h \
	PosLonCarr.h \
	PosPillar.h \
	PostCrashSubCauseCode.h \
	PreemptPriorityList.h \
	PrioritizationResponse.h \
	PrioritizationResponseList.h \
	PrioritizationResponseStatus.h \
	PriorityRequestType.h \
	ProtectedCommunicationZone.h \
	ProtectedCommunicationZonesRSU.h \
	ProtectedZoneID.h \
	ProtectedZoneRadius.h \
	ProtectedZoneType.h \
	Provider.h \
	PtActivationData.h \
	PtActivation.h \
	PtActivationType.h \
	PtvRequestType.h \
	PublicTransportContainer.h \
	RccPart.h \
	ReferenceDenms.h \
	ReferencePosition.h \
	RegionalExtension.h \
	RegionId.h \
	RegulatorySpeedLimit.h \
	RelevanceDistance.h \
	RelevanceTrafficDirection.h \
	RequestID.h \
	RequestImportanceLevel.h \
	RequestorDescription.h \
	RequestorPositionVector.h \
	RequestorType.h \
	RequestResponseIndication.h \
	RequestSubRole.h \
	RescueAndRecoveryWorkInProgressSubCauseCode.h \
	RescueContainer.h \
	RestrictedTypes.h \
	RestrictionAppliesTo.h \
	RestrictionClassAssignment.h \
	RestrictionClassID.h \
	RestrictionClassList.h \
	RestrictionUserType-addGrpC.h \
	RestrictionUserType.h \
	RestrictionUserTypeList.h \
	RoadConfigurationContainer.h \
	RoadLaneSetList.h \
	RoadRegulatorID.h \
	RoadSegment.h \
	RoadSegmentID.h \
	RoadSegmentList.h \
	RoadSegmentReferenceID.h \
	RoadType.h \
	RoadwayCrownAngle.h \
	RoadWorksContainerBasic.h \
	RoadWorksContainerExtended.h \
	RoadworksSubCauseCode.h \
	ROI.h \
	RSCode.h \
	RSCUnit.h \
	RSUContainerHighFrequency.h \
	SafetyCarContainer.h \
	Scale-B12.h \
	SegmentAttributeXY.h \
	SegmentAttributeXYList.h \
	Segment.h \
	SemiAxisLength.h \
	SequenceNumber.h \
	SignalControlZone.h \
	SignalGroupID.h \
	SignalHeadLocation.h \
	SignalHeadLocationList.h \
	SignalRequesterInfo.h \
	SignalRequest.h \
	SignalRequestList.h \
	SignalRequestMessage.h \
	SignalRequestPackage.h \
	SignalStatus.h \
	SignalStatusList.h \
	SignalStatusMessage.h \
	SignalStatusPackage-addGrpC.h \
	SignalStatusPackage.h \
	SignalStatusPackageList.h \
	SignalViolationSubCauseCode.h \
	SituationContainer.h \
	SlowVehicleSubCauseCode.h \
	SoundLevel.h \
	SPATEM.h \
	SPAT.h \
	SpecialTransportContainer.h \
	SpecialTransportType.h \
	SpecialVehicleContainer.h \
	SpeedAdvice.h \
	SpeedConfidence.h \
	Speed.h \
	SpeedLimit.h \
	SpeedLimitList.h \
	SpeedLimitType.h \
	SpeedValue.h \
	SPE.h \
	SREM.h \
	SSEM.h \
	StationarySince.h \
	StationaryVehicleContainer.h \
	StationaryVehicleSubCauseCode.h \
	StationID.h \
	StationType.h \
	SteeringWheelAngleConfidence.h \
	SteeringWheelAngle.h \
	SteeringWheelAngleValue.h \
	SubCauseCodeType.h \
	TcPart.h \
	Temperature.h \
	TemporaryID.h \
	Termination.h \
	TextContainer.h \
	Text.h \
	TimeChangeDetails.h \
	TimeIntervalConfidence.h \
	TimeMark.h \
	TimeReference.h \
	TimestampIts.h \
	Traces.h \
	TractorCharacteristics.h \
	TrafficConditionSubCauseCode.h \
	TrafficRule.h \
	TrailerCharacteristics.h \
	TrainCharacteristics.h \
	TransitVehicleOccupancy.h \
	TransitVehicleStatus.h \
	TransmissionAndSpeed.h \
	TransmissionInterval.h \
	TransmissionState.h \
	TurningRadius.h \
	UnitType.h \
	ValidityDuration.h \
	VarLengthNumber.h \
	VcClass.h \
	VcCode.h \
	VcOption.h \
	VDS.h \
	VED.h \
	VehicleBreakdownSubCauseCode.h \
	VehicleCharacteristicsFixValues.h \
	VehicleCharacteristicsRanges.h \
	VehicleDimensions.h \
	VehicleIdentification.h \
	VehicleID.h \
	VehicleLengthConfidenceIndication.h \
	VehicleLength.h \
	VehicleLengthValue.h \
	VehicleMass.h \
	VehicleRole.h \
	VehicleType.h \
	VehicleWeightLimits.h \
	VehicleWidth.h \
	Velocity.h \
	VerticalAcceleration.h \
	VerticalAccelerationValue.h \
	WaitOnStopline.h \
	Weight.h \
	WheelBaseVehicle.h \
	WMInumber.h \
	WrongWayDrivingSubCauseCode.h \
	YawRateConfidence.h \
	YawRate.h \
	YawRateValue.h \
	Zid.h \
	Zone.h \
	ZoneLength.h

	its_headers.path = ../../include/aimsun_extensions/V2XFramework/ITS-spec
	for (header, ITS-spec_headers) {
		its_headers.files += $${SOURCES_DIR}/aimsun_extensions/V2XFramework/ITS-spec/$$header
	}

	INSTALLS += its_headers
	PRE_TARGETDEPS += install_its_headers

	asn_spec.path = ../../specifications

	asn_spec_headers = ITS-spec/ETSI_TS_103301.asn ITS-spec/ISO_TS_14906_Application.asn ITS-spec/ISO_TS_17419.asn \
	ITS-spec/ISO_TS_19321.asn    ITS-spec/LibIts-CAM-r1318.asn \
	ITS-spec/LibIts-ITS-Container-r1318.asn \
	ITS-spec/ISO_TS_14816.asn    ITS-spec/ISO_TS_14906_Generic.asn \
	ITS-spec/ISO_TS_19091.asn  ITS-spec/ISO_TS_24534-3.asn \
	ITS-spec/LibIts-DENM-r1318.asn

	for (spec, asn_spec_headers) {
		asn_spec.files += $${SOURCES_DIR}/aimsun_extensions/V2XFramework/$$spec
	}
	INSTALLS += asn_spec
	PRE_TARGETDEPS += install_asn_spec

} else {
	message("User build")
}

PREFIX_INCLUDEPATH = $${AIMSUN_SDK_DIR}
INCLUDEPATH += $$PREFIX_INCLUDEPATH/core/random
INCLUDEPATH += $$PREFIX_INCLUDEPATH/core/ang_kernel
INCLUDEPATH += $$PREFIX_INCLUDEPATH/core/ANG_DTA/ADynamicAPI
INCLUDEPATH += $$PREFIX_INCLUDEPATH/aimsun_extensions/V2XFramework
INCLUDEPATH += $$PREFIX_INCLUDEPATH/aimsun_extensions/V2XFramework/ASN1
INCLUDEPATH += $$PREFIX_INCLUDEPATH/aimsun_extensions/V2XFramework/ITS-spec

DEPENDPATH += $$INCLUDEPATH

win32 {
	LIBS += -L$${BIN_PATH} -ladynamicapi8 -lV2XFramework8
} macx {
	LIBS += $$QWT_LIBS $$GDAL_LIBS $$QSCINDILLA_LIBS
	LIBS += -L$${BIN_PATH}/AIMSUN.app/Contents/Frameworks -ladynamicapi -lV2XFramework
} linux {
	LIBS += $$QWT_LIBS $$GDAL_LIBS $$QSCINDILLA_LIBS
	LIBS += -L$${BIN_PATH} -ladynamicapi -lV2XFramework

	QMAKE_CXXFLAGS += -Werror
}

#-------------------------------------------------------------------------------------
