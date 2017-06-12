/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#include "FlourishAP.h"
#include <DENMMessage.h>
#include <CAMMessage.h>
#include <SPATEMMessage.h>
#include <MAPEMMessage.h>

FlourishAP::FlourishAP(quint32 id, const GKObject *obj) : V2XSimpleAP(id, obj)
{

}

PacketPointer FlourishAP::generateDENM()
{
	qDebug() << V2XNetworkNode::getId() << "is generating a DENMMessage";

	DENMMessage *msg = new DENMMessage();
	msg->initializeEmpty();
	DENM_t *data = msg->data();

	// ItsPduHeader
	data->header.messageID = messageID_denm;
	data->header.protocolVersion = protocolVersion_currentVersion;
	data->header.stationID = V2XNetworkNode::getId();

	return PacketPointer(msg);
}

PacketPointer FlourishAP::generateMAPEM(const V2XIntersectionPointer &control)
{
	Q_UNUSED(control);
	qDebug() << V2XNetworkNode::getId() << "is generating a MAPEMMessage";

	MAPEMMessage *msg = new MAPEMMessage ();
	msg->initializeEmpty();

	MAPEM_t *data = msg->data();
	data->header.messageID = messageID_mapem;
	data->header.protocolVersion = protocolVersion_currentVersion;
	data->header.stationID = V2XNetworkNode::getId();

	// IT CONTAINS BUG!
	//control->getMapData(&data->map);

	return PacketPointer(msg);
}

PacketPointer FlourishAP::generateSPATEM(const V2XIntersectionPointer &control)
{
	qDebug() << V2XNetworkNode::getId() << "is generating a SPATEMMessage";
	Q_UNUSED(control);

	SPATEMMessage *msg = new SPATEMMessage ();
	msg->initializeEmpty();

	SPATEM_t *data = msg->data();

	data->header.messageID = messageID_spatem;
	data->header.protocolVersion = protocolVersion_currentVersion;
	data->header.stationID = V2XNetworkNode::getId();

	/*
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
	*/

	return PacketPointer(msg);
}

PacketPointerList FlourishAP::generateMessage()
{
	PacketPointerList list;
	list.append(generateDENM());

	for (V2XIntersectionPointer control : m_connectedIntersections) {
		qDebug() << "Generating messages for the control";
		list.append(generateMAPEM(control));
		list.append(generateSPATEM(control));
	}

	return list;
}

void FlourishAP::received (const QPointer<NetDevice> &device,
						   const QSharedPointer<const Packet> &packet, const Address &addr)
{
	Q_UNUSED(device);
	Q_UNUSED(addr);

	const QSharedPointer<const CAMMessage> cam = qSharedPointerDynamicCast<const CAMMessage>(packet);
	if (cam != nullptr) {
		m_engine.evaluate(cam, this);
		return;
	}

	const QSharedPointer<const DENMMessage> denm = qSharedPointerDynamicCast<const DENMMessage> (packet);
	if (denm != nullptr) {
		m_engine.evaluate(denm, this);
		return;
	}


	const QSharedPointer<const SPATEMMessage> spatem = qSharedPointerDynamicCast<const SPATEMMessage> (packet);
	if (spatem != nullptr) {
		m_engine.evaluate(spatem, this);
		return;
	}

	const QSharedPointer<const MAPEMMessage> mapem = qSharedPointerDynamicCast<const MAPEMMessage> (packet);
	if (mapem != nullptr) {
		m_engine.evaluate(mapem, this);
		return;
	}

	qDebug () << "RECEIVED GARBAGE";
}
