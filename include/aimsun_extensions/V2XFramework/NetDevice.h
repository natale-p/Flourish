/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "Packet.h"
#include <QSharedPointer>
#include "V2XFrameworkUtil.h"

// Very basic because right now we don't need any address at all;
// For sure it will change in the future in an interface class
typedef QString Address;

class V2XNetworkNode;

/**
 * \ingroup V2XFramework
 * \brief The NetDevice class
 */
class V2XFRAMEWORKEXPORT NetDevice : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(NetDevice)

public:
	NetDevice() : QObject () { }
	virtual ~NetDevice() { }

	/**
	 * \brief Determine if the device is up or not
	 * \return true if it is up (attached to a channel)
	 */
	virtual bool isUp () const = 0;

	/**
	 * \brief Send a packet to a destination
	 * \param packet packet to send
	 * \param dest destination
	 * \return true if the packet is enqueued successfully for transmission
	 */
	virtual bool send (QSharedPointer<Packet> packet, const Address& dest) = 0;
	/**
	 * \brief Send a packet to a destination from a source
	 * \param packet packet to send
	 * \param source source address
	 * \param dest destination address
	 * \return true if the packet is enqueued successfully for transmission
	 */
	virtual bool sendFrom (QSharedPointer<Packet> packet, const Address& source, const Address& dest) = 0;

	/**
	 * \brief Get the node associated
	 * \return The node
	 */
	virtual V2XNetworkNode* getNode (void) const = 0;

signals:
	/**
	 * \brief Emitted when a packet is received from a channel
	 * \param device
	 * \param packet Packet
	 * \param addr Address
	 */
	void received (const QPointer<NetDevice> &device,
				   const QSharedPointer<const Packet> &packet, const Address &addr);
};
