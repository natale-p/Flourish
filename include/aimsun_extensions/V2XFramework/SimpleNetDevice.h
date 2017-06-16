/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "NetDevice.h"
#include "SimpleChannel.h"
#include "V2XFrameworkUtil.h"

/**
 * \ingroup V2XFramework
 * \brief A simple NetDevice
 *
 * All the logic behind this class is in the methods attach and detach.
 * Basically, it represents a device which can connect to many channels, and
 * that can do a broadcast of Packets to all the other devices attached to
 * them.
 *
 * A send operation is modeled as a cycle, in which the class calls the method
 * SimpleChannel::broadcast over all attached channels. At the receive time,
 * the method packetReceived will be called by the SimpleChannel class.
 * For this and other details, please have a look to its documentation.
 *
 * \see SimpleChannel
 */
class V2XFRAMEWORKEXPORT SimpleNetDevice  : public NetDevice
{
	Q_OBJECT
	Q_DISABLE_COPY(SimpleNetDevice)

public:
	/**
	 * \brief Constructor
	 */
	SimpleNetDevice();
	/**
	 * \brief Deconstructor
	 */
	virtual ~SimpleNetDevice();

	// public interface
	/**
	 * \brief Set the owner node
	 * \param node owner
	 */
	void setNode(V2XNetworkNode *node);

	/**
	 * \brief Attach to a channel
	 * \param channel Channel
	 */
	virtual void attach (SimpleChannel *channel);
	/**
	 * \brief Detach from a channel
	 * \param channel Channnel
	 */
	virtual void detach (SimpleChannel *channel);

	/**
	 * \brief Get the address which represents the broadcast
	 * \return the address which represents the broadcast
	 */
	Address getBroadcastAddress();

	/**
	 * \brief Get the number of devices attached to the channels to which this
	 * device is attached to
	 * \return a number
	 */
	quint32 devicesConnectedToAttachedChannels() const;

	/**
	 * \brief A packet has been received
	 *
	 * It emits the received signal, to which the owning class should connect
	 * to.
	 *
	 * \param packet Received packet
	 */
	void packetReceived (const QSharedPointer<const Packet> &packet);

	// inherit from NetDevice
	virtual bool send (QSharedPointer<Packet> packet, const Address& dest) Q_DECL_OVERRIDE;
	virtual bool sendFrom (QSharedPointer<Packet> packet, const Address& source, const Address& dest) Q_DECL_OVERRIDE;
	virtual V2XNetworkNode* getNode () const Q_DECL_OVERRIDE;
	virtual bool isUp () const Q_DECL_OVERRIDE;

public slots:
	/**
	 * \brief Called when a channel we were attached to is destroyed
	 * \param channel Channel destroyed
	 */
	void channelRemoved(SimpleChannel *channel);

private:
	QMap<quint32, SimpleChannel*> m_channels; //!< The list of attached channel
	V2XNetworkNode *m_node; //!< The owner
	QMap<quint32, QMetaObject::Connection> m_connections; //!< The list of connections to the destroyed signal
};

