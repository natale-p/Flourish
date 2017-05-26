SUB_PROJECT_NAME = FlourishV2XFramework
BASE_DIR = ../../../..
include (../../config.incl)

SOURCES += \
	FlourishConnectedAgent.cpp \
	FlourishV2XFramework.cpp \
	FlourishVehicleRulesEngine.cpp \
	FlourishBroker.cpp \
    FlourishAP.cpp

HEADERS += \
	FlourishV2XFrameworkUtil.h \
	FlourishConnectedAgent.h \
	FlourishV2XFramework.h \
	FlourishVehicleRulesEngine.h \
	FlourishBroker.h \
    FlourishAP.h

macx {
	TARGET = $${BIN_PATH}/Aimsun.app/Contents/PlugIns/dynamicAPIS/FlourishV2XFramework
	QMAKE_LFLAGS_SONAME  = -Wl,-install_name,@rpath/
}else{
	TARGET = $${BIN_PATH}/plugins/dynamicAPIS/FlourishV2XFramework
}

#-------------------------------------------------------------------------------------

TEMPLATE = lib
VERSION = 8.2.0

CONFIG += dll qt thread exceptions rtti

win32 {
    DEFINES += _FlourishV2XFrameworkEXTDLL_DEF
}

QT += sql xml widgets

contains(DEVELOPER, true) {
	message("Developer build; install headers enabled")
	PREFIX_INCLUDEPATH = $${SOURCES_DIR}

#	core_ang_dta_headers.path = ../../include/core/ANG_DTA
#	core_ang_dta_headers.files += $${SOURCES_DIR}/core/ANG_DTA/DTAUtil.h

#	INSTALLS += core_ang_dta_headers
#	PRE_TARGETDEPS += install_core_ang_dta_headers

#	core_ang_kernel_headers.path = ../../include/core/ang_kernel
#	core_ang_kernel_headers.files += $${SOURCES_DIR}/core/ang_kernel/GKGeoUtil.h
#	core_ang_kernel_headers.files += $${SOURCES_DIR}/core/ang_kernel/GKObject.h
#	core_ang_kernel_headers.files += $${SOURCES_DIR}/core/ang_kernel/GKType.h
#	core_ang_kernel_headers.files += $${SOURCES_DIR}/core/ang_kernel/GKColumn.h
#	core_ang_kernel_headers.files += $${SOURCES_DIR}/core/ang_kernel/GKUtil.h

#	INSTALLS += core_ang_kernel_headers
#	PRE_TARGETDEPS += install_core_ang_kernel_headers

#	random_headers.path = ../../include/core/random
#	random_headers.files += $${SOURCES_DIR}/core/random/FRand.h

#	INSTALLS += random_headers
#	PRE_TARGETDEPS += install_random_headers

	networkgui_headers.path = ../../include/plugins/NetworkGUI/
	networkgui_headers.files += $${SOURCES_DIR}/plugins/NetworkGUI/NetworkGUIAP.h

	INSTALLS += networkgui_headers
	PRE_TARGETDEPS += install_networkgui_headers

	adynamic_api_headers.path = ../../include/core/ANG_DTA/ADynamicAPI
	adynamic_api_headers.files += $${SOURCES_DIR}/core/ANG_DTA/ADynamicAPI/ADynamicAgent.h
	adynamic_api_headers.files += $${SOURCES_DIR}/core/ANG_DTA/ADynamicAPI/ADynamicAPI.h
	adynamic_api_headers.files += $${SOURCES_DIR}/core/ANG_DTA/ADynamicAPI/ADynamicAPISetup.h

	INSTALLS += adynamic_api_headers
	PRE_TARGETDEPS += install_adynamic_api_headers

	V2XFramework_headers = Aggregate.h \
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
	V2XFramework.h \
	V2XFrameworkUtil.h \
	V2XMessage.h \
	VehicleRulesEngine.h \
	V2XNetworkNode.h

	v2x_framework_headers.path = ../../include/aimsun_extensions/V2XFramework
	for (header, V2XFramework_headers) {
		v2x_framework_headers.files += $${SOURCES_DIR}/aimsun_extensions/V2XFramework/$$header
	}

	INSTALLS += v2x_framework_headers
	PRE_TARGETDEPS += install_v2x_framework_headers

	ASN_headers = asn_application.h  asn_internal.h     asn_system.h      ber_tlv_tag.h  constraints.h\
	constr_SEQUENCE_OF.h  der_encoder.h  INTEGER.h           OCTET_STRING.h\
	per_opentype.h  xer_decoder.h \
	asn_codecs.h       asn_SEQUENCE_OF.h  ber_decoder.h     BIT_STRING.h\
	constr_CHOICE.h    constr_SET_OF.h ENUMERATED.h NativeEnumerated.h per_decoder.h \
	per_support.h   xer_encoder.h asn_codecs_prim.h  asn_SET_OF.h ber_tlv_length.h  \
	BOOLEAN.h      constr_SEQUENCE.h  constr_TYPE.h IA5String.h NativeInteger.h per_encoder.h   UTF8String.h    xer_support.h

	asn1_headers.path = ../../include/aimsun_extensions/V2XFramework/ASN1
	for (header, ASN_headers) {
		asn1_headers.files += $${SOURCES_DIR}/aimsun_extensions/V2XFramework/ASN1/$$header
	}

	INSTALLS += asn1_headers
	PRE_TARGETDEPS += install_asn1_headers

	ITS-spec_headers = AccelerationConfidence.h \
	AccelerationControl.h \
	AccidentSubCauseCode.h \
	ActionID.h \
	AdverseWeatherCondition-AdhesionSubCauseCode.h \
	AdverseWeatherCondition-ExtremeWeatherConditionSubCauseCode.h \
	AdverseWeatherCondition-PrecipitationSubCauseCode.h \
	AdverseWeatherCondition-VisibilitySubCauseCode.h \
	AlacarteContainer.h \
	AltitudeConfidence.h \
	Altitude.h \
	AltitudeValue.h \
	BasicContainer.h \
	BasicVehicleContainerHighFrequency.h \
	BasicVehicleContainerLowFrequency.h \
	CAM.h \
	CamParameters.h \
	CauseCode.h \
	CauseCodeType.h \
	CenDsrcTollingZone.h \
	CenDsrcTollingZoneID.h \
	ClosedLanes.h \
	CollisionRiskSubCauseCode.h \
	CoopAwareness.h \
	CurvatureCalculationMode.h \
	CurvatureConfidence.h \
	Curvature.h \
	CurvatureValue.h \
	DangerousEndOfQueueSubCauseCode.h \
	DangerousGoodsBasic.h \
	DangerousGoodsContainer.h \
	DangerousGoodsExtended.h \
	DangerousSituationSubCauseCode.h \
	DecentralizedEnvironmentalNotificationMessage.h \
	DeltaAltitude.h \
	DeltaLatitude.h \
	DeltaLongitude.h \
	DeltaReferencePosition.h \
	DENM.h \
	DriveDirection.h \
	DrivingLaneStatus.h \
	EmbarkationStatus.h \
	EmergencyContainer.h \
	EmergencyPriority.h \
	EmergencyVehicleApproachingSubCauseCode.h \
	EnergyStorageType.h \
	EventHistory.h \
	EventPoint.h \
	ExteriorLights.h \
	GenerationDeltaTime.h \
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
	HumanPresenceOnTheRoadSubCauseCode.h \
	HumanProblemSubCauseCode.h \
	ImpactReductionContainer.h \
	InformationQuality.h \
	ItineraryPath.h \
	ItsPduHeader.h \
	LanePosition.h \
	LateralAcceleration.h \
	LateralAccelerationValue.h \
	Latitude.h \
	LightBarSirenInUse.h \
	LocationContainer.h \
	Longitude.h \
	LongitudinalAcceleration.h \
	LongitudinalAccelerationValue.h \
	LowFrequencyContainer.h \
	ManagementContainer.h \
	NumberOfOccupants.h \
	PathDeltaTime.h \
	PathHistory.h \
	PathPoint.h \
	PerformanceClass.h \
	PosCentMass.h \
	PosConfidenceEllipse.h \
	PosFrontAx.h \
	PositioningSolutionType.h \
	PositionOfOccupants.h \
	PositionOfPillars.h \
	PosLonCarr.h \
	PosPillar.h \
	PostCrashSubCauseCode.h \
	ProtectedCommunicationZone.h \
	ProtectedCommunicationZonesRSU.h \
	ProtectedZoneID.h \
	ProtectedZoneRadius.h \
	ProtectedZoneType.h \
	PtActivationData.h \
	PtActivation.h \
	PtActivationType.h \
	PublicTransportContainer.h \
	ReferenceDenms.h \
	ReferencePosition.h \
	RelevanceDistance.h \
	RelevanceTrafficDirection.h \
	RequestResponseIndication.h \
	RescueAndRecoveryWorkInProgressSubCauseCode.h \
	RescueContainer.h \
	RestrictedTypes.h \
	RoadType.h \
	RoadWorksContainerBasic.h \
	RoadWorksContainerExtended.h \
	RoadworksSubCauseCode.h \
	RSUContainerHighFrequency.h \
	SafetyCarContainer.h \
	SemiAxisLength.h \
	SequenceNumber.h \
	SignalViolationSubCauseCode.h \
	SituationContainer.h \
	SlowVehicleSubCauseCode.h \
	SpecialTransportContainer.h \
	SpecialTransportType.h \
	SpecialVehicleContainer.h \
	SpeedConfidence.h \
	Speed.h \
	SpeedLimit.h \
	SpeedValue.h \
	StationarySince.h \
	StationaryVehicleContainer.h \
	StationaryVehicleSubCauseCode.h \
	StationID.h \
	StationType.h \
	SteeringWheelAngleConfidence.h \
	SteeringWheelAngle.h \
	SteeringWheelAngleValue.h \
	SubCauseCodeType.h \
	Temperature.h \
	Termination.h \
	TimestampIts.h \
	Traces.h \
	TrafficConditionSubCauseCode.h \
	TrafficRule.h \
	TransmissionInterval.h \
	TurningRadius.h \
	ValidityDuration.h \
	VDS.h \
	VehicleBreakdownSubCauseCode.h \
	VehicleIdentification.h \
	VehicleLengthConfidenceIndication.h \
	VehicleLength.h \
	VehicleLengthValue.h \
	VehicleMass.h \
	VehicleRole.h \
	VehicleWidth.h \
	VerticalAcceleration.h \
	VerticalAccelerationValue.h \
	WheelBaseVehicle.h \
	WMInumber.h \
	WrongWayDrivingSubCauseCode.h \
	YawRateConfidence.h \
	YawRate.h \
	YawRateValue.h

	its_headers.path = ../../include/aimsun_extensions/V2XFramework/ITS-spec
	for (header, ITS-spec_headers) {
		its_headers.files += $${SOURCES_DIR}/aimsun_extensions/V2XFramework/ITS-spec/$$header
	}

	INSTALLS += its_headers
	PRE_TARGETDEPS += install_its_headers

} else {
	message("User build")
	PREFIX_INCLUDEPATH = $${AIMSUN_SDK_DIR}
}

INCLUDEPATH += $$PREFIX_INCLUDEPATH/core/random
INCLUDEPATH += $$PREFIX_INCLUDEPATH/core/ang_kernel
INCLUDEPATH += $$PREFIX_INCLUDEPATH/core/ANG_DTA
INCLUDEPATH += $$PREFIX_INCLUDEPATH/core/ANG_DTA/ADynamicAPI
INCLUDEPATH += $$PREFIX_INCLUDEPATH/aimsun_extensions/V2XFramework
INCLUDEPATH += $$PREFIX_INCLUDEPATH/aimsun_extensions/V2XFramework/ASN1
INCLUDEPATH += $$PREFIX_INCLUDEPATH/aimsun_extensions/V2XFramework/ITS-spec
INCLUDEPATH += $$PREFIX_INCLUDEPATH/plugins/NetworkGUI

DEPENDPATH += $$INCLUDEPATH

win32 {
	LIBS += -L$${BIN_PATH} -langkernel -lV2XFramework8
	LIBS += -L$${PLG_PATH} -ldtakernel8 -lNetworkGUI8
} macx {
	LIBS += $$QWT_LIBS $$GDAL_LIBS $$QSCINDILLA_LIBS
	LIBS += -L$${BIN_PATH}/AIMSUN.app/Contents/PlugIns -ldtakernel -lNetworkGUI
	LIBS += -L$${BIN_PATH}/AIMSUN.app/Contents/Frameworks -langkernel -lV2XFramework
} linux {
	LIBS += $$QWT_LIBS $$GDAL_LIBS $$QSCINDILLA_LIBS
	LIBS += -L$${PLG_PATH} -ldtakernel -lNetworkGUI
	LIBS += -L$${BIN_PATH} -langkernel -lV2XFramework
}

#-------------------------------------------------------------------------------------
