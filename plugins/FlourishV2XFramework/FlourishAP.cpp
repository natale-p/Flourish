/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#include "FlourishAP.h"
#include <DENMMessage.h>
#include <CAMMessage.h>
#include <SPATEMMessage.h>

FlourishAP::FlourishAP(const GKObject *obj) : V2XSimpleAP(obj)
{

}

PacketPointer FlourishAP::generateDENM()
{
	DENMMessage *msg = new DENMMessage();
	msg->initializeEmpty();
	DENM_t *data = msg->data();

	// ItsPduHeader
	data->header.messageID = messageID_denm;
	data->header.protocolVersion = protocolVersion_currentVersion;
	data->header.stationID = V2XNetworkNode::getId();

	return PacketPointer(msg);
}

PacketPointer FlourishAP::generateSPATEM(const V2XConnectedControlPointer &control)
{
	SPATEMMessage *msg = new SPATEMMessage ();
	msg->initializeEmpty();

	SPATEM_t *data = msg->data();

	data->header.messageID = messageID_spatem;
	data->header.protocolVersion = protocolVersion_currentVersion;
	data->header.stationID = V2XNetworkNode::getId();

	IntersectionState *state = (IntersectionState*) calloc (1, sizeof(*state));
	state->id.id = control->getId ();
	state->revision = 0;
	control->getIntersectionState(&state->status);

	MovementState *movement = (MovementState*) calloc (1, sizeof (*movement));
	movement->signalGroup = 0;
	
	MovementEvent *event = (MovementEvent*) calloc (1, sizeof (*event));
	control->getMovementPhaseState(&event->eventState);

	TimeChangeDetails *timeChangeDetails = (TimeChangeDetails*) calloc (1, sizeof(TimeChangeDetails));
	control->getTimingsChangeDetails (timeChangeDetails);
	event->timing = timeChangeDetails;

	asn_sequence_add(&movement->state_time_speed, event);

	asn_sequence_add(&state->states, movement);

	asn_sequence_add (&data->spat.intersections, state);

	return PacketPointer(msg);
}

PacketPointerList FlourishAP::generateMessage()
{
	qDebug() << V2XNetworkNode::getId() << "is generating a DENMMessage";

	PacketPointerList list;
	list.append(generateDENM());

	for (V2XConnectedControlPointer control : m_controlList) {
		list.append(generateSPATEM(control));
	}

	return list;
}

void FlourishAP::received (const QPointer<NetDevice> &device,
						   const QSharedPointer<const Packet> &packet, const Address &addr)
{
	Q_UNUSED(device);
	Q_UNUSED(packet);
	Q_UNUSED(addr);

	const QSharedPointer<const CAMMessage> cam = qSharedPointerDynamicCast<const CAMMessage>(packet);

	if (cam == nullptr) {
		const QSharedPointer<const DENMMessage> denm = qSharedPointerDynamicCast<const DENMMessage> (packet);
		//Q_ASSERT (denm != nullptr);
		if (denm != nullptr) {
			qDebug() << V2XNetworkNode::getId() << "received DENMMessage";
		} else {
			qDebug() << V2XNetworkNode::getId() << "RECEIVED GARBAGE";
		}
	} else {
		qDebug() << V2XNetworkNode::getId() << "received CAMMessage";
	}
}
