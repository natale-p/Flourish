/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#include "FlourishAP.h"
#include <DENMMessage.h>
#include <CAMMessage.h>

FlourishAP::FlourishAP(const GKPoint &position) : V2XSimpleAP(position)
{

}

QSharedPointer<Packet> FlourishAP::generateMessage()
{
	qDebug() << V2XNetworkNode::getId() << "is generating a DENMMessage";

	DENMMessage *msg = new DENMMessage();
	msg->initializeEmpty();
	DENM_t *data = msg->data();

	// ItsPduHeader
	data->header.messageID = messageID_denm;
	data->header.protocolVersion = protocolVersion_currentVersion;
	data->header.stationID = V2XNetworkNode::getId();

	return QSharedPointer<Packet>(msg);
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
