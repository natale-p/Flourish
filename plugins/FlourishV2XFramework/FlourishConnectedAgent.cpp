/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#include "FlourishConnectedAgent.h"
#include "FlourishBroker.h"
#include "CAMMessage.h"
#include "DENMMessage.h"
#include "SPATEMMessage.h"

FlourishConnectedAgent::FlourishConnectedAgent(quint32 idhandler, DTAVeh *agent,
											   FlourishBroker *broker) :
	V2XConnectedAgent(idhandler, agent),
	m_broker (broker)
{
}

void FlourishConnectedAgent::received (const QPointer<NetDevice> &device,
									   const QSharedPointer<const Packet> &packet,
									   const Address &addr)
{
	Q_UNUSED(device);
	Q_UNUSED(addr);

	const QSharedPointer<const CAMMessage> cam = qSharedPointerDynamicCast<const CAMMessage>(packet);
	if (cam != nullptr) {
		m_engine.evaluate(cam, dynamic_cast<V2XConnectedAgent*> (this));
		return;
	}

	const QSharedPointer<const DENMMessage> denm = qSharedPointerDynamicCast<const DENMMessage> (packet);
	if (denm != nullptr) {
		m_engine.evaluate(denm, dynamic_cast<V2XConnectedAgent*> (this));
		return;
	}


	const QSharedPointer<const SPATEMMessage> spatem = qSharedPointerDynamicCast<const SPATEMMessage> (packet);
	if (spatem != nullptr) {
		m_engine.evaluate(spatem, dynamic_cast<V2XConnectedAgent*> (this));
		return;
	}

	qDebug () << "RECEIVED GARBAGE";
}


PacketPointerList FlourishConnectedAgent::generateMessage()
{
	qDebug() << V2XNetworkNode::getId() << "is generating a CAMMessage";

	CAMMessage *msg = new CAMMessage();
	msg->initializeEmpty();
	CAM_t *data = msg->data();

	// ItsPduHeader
	data->header.messageID = messageID_cam;
	data->header.protocolVersion = protocolVersion_currentVersion;
	data->header.stationID = V2XNetworkNode::getId();

	// CoopAwareness
	data->cam.generationDeltaTime = V2XNetworkNode::getCurrentTime().getMilliseconds();

	// CAM parameters
	// Basic Container
	data->cam.camParameters.basicContainer.stationType = StationType_passengerCar; // TODO: BUSSes
	data->cam.camParameters.basicContainer.referencePosition.latitude = getPosition().x;
	data->cam.camParameters.basicContainer.referencePosition.longitude = getPosition().y;
	data->cam.camParameters.basicContainer.referencePosition.altitude.altitudeValue = getPosition().z;

	// High Frequency Container
	BasicVehicleContainerHighFrequency_t & basicVehicleContainerHighFrequency = data->cam.camParameters.highFrequencyContainer.choice.basicVehicleContainerHighFrequency;
	basicVehicleContainerHighFrequency.heading.headingValue = HeadingValue_unavailable;
	basicVehicleContainerHighFrequency.speed.speedValue = getSpeed();

	basicVehicleContainerHighFrequency.driveDirection = DriveDirection_forward;

	basicVehicleContainerHighFrequency.vehicleLength.vehicleLengthValue = getLength();
	basicVehicleContainerHighFrequency.vehicleWidth = getWidth();
	basicVehicleContainerHighFrequency.longitudinalAcceleration.longitudinalAccelerationValue = getAcceleration();
	basicVehicleContainerHighFrequency.curvature.curvatureValue = 0;

	basicVehicleContainerHighFrequency.curvatureCalculationMode = CurvatureCalculationMode_unavailable;

	PacketPointerList list;
	list.append(PacketPointer(msg));
	return list;
}

QSet<V2XNetworkNode *> FlourishConnectedAgent::getNearestStations(const V2XNetworkNode *target) const
{
	return m_broker->getNearestStations(qobject_cast<const V2XSimpleAP*> (target));
}

QSet<V2XNetworkNode*> FlourishConnectedAgent::getNearestAgent(const V2XNetworkNode *station) const
{
	return m_broker->getNearestAgent(qobject_cast<const V2XSimpleAP*> (station));
}
