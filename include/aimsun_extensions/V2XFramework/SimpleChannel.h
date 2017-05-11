/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "Channel.h"
#include "ErrorModel.h"
#include "V2XFrameworkUtil.h"

class SimpleNetDevice;

/**
 * \ingroup V2XFramework
 * \brief A simple channel class
 *
 * It has a concept of propagation delay and can use an error model to
 * determine the error on each packet that passes over the channel.
 *
 * The channel provide a simple functionality for doing a broadcast
 * between all the connected devices. It is strictly connected to the
 * class SimpleNetDevice.
 *
 * A device should register itself through the attach method (and, therefore,
 * detach it when it is appropriate through the detach method).
 * Then, to send a message, the device should call the broadcast method
 * that calculates the delivery time, and save the pair delivery time - message
 * into an internal queue.
 *
 * To deliver the messages enqueued, the owner of the Channel should call the
 * sendUpTo method, specifying a time. All the messages enqued for a delivery
 * time which is less or equal to the one specified will be delivered to the
 * attached devices.
 *
 * In this way, it is modeled the possibility of a vehicle A which is in the range
 * of the vehicle B at the time of the sending, but then A leaves the range at
 * the time of delivery, and therefore should not be able to receive the message.
 *
 * \see sendUpTo
 * \see broadcast
 */
class V2XFRAMEWORKEXPORT SimpleChannel : public Channel
{
	Q_OBJECT
	Q_DISABLE_COPY(SimpleChannel)

public:
	/**
	 * \brief Constructor
	 */
	SimpleChannel();
	/**
	 * \brief Deconstructor
	 */
	virtual ~SimpleChannel();

	// Public interface (users can freely call them)

	/**
	 * \brief Deliver to the current registered stations the messages enqueued
	 * up to the time specified
	 *
	 * \param time Time
	 */
	void sendUpTo (double time);

	/**
	 * \brief set the delay of this channel
	 *
	 * TODO: Use an appropriate class instead of double which represent seconds
	 *
	 * \param delay the delay
	 */
	void setDelay (double delay);

	/**
	 * \brief set the error model of this channel
	 *
	 * \param errorModel the error model
	 */
	void setErrorModel (const QSharedPointer<ErrorModel> &errorModel);

	// inherited
	virtual quint32 getNDevices (void) const Q_DECL_OVERRIDE;

signals:
	/**
	 * \brief Emitted when the channel is about to be destroyed
	 * \param channel (this) channel
	 */
	void destroyed(SimpleChannel *channel);

	/**
	 * \brief Emitted when a device is attaching to this channel
	 * \param device device attaching
	 */
	void attachedTo(NetDevice *device);

	/**
	 * \brief Emitted when a device is detaching from this channel
	 * \param device device detaching
	 */
	void detachedFrom(NetDevice *device);

protected:
	// These can be called from outside only, and in particular from
	// SimpleNetDevice

	/**
	 * \brief attach a device to this channel
	 * \param netDevice the netdevice to attach
	 */
	void attach (NetDevice *device);

	/**
	 * \brief detach detach a device from this channel
	 * \param deviceId The netdevice to detach
	 */
	void detach (NetDevice *device);

	/**
	 * \brief broadcast a packet to all attached devices
	 *
	 *
	 *
	 * \param packet the packet to transmit
	 * \param srcNetDevice the source of the packet
	 * \return true if success
	 */
	virtual bool broadcast (const QSharedPointer<Packet> &packet,
							const NetDevice *srcNetDevice);

	friend class SimpleNetDevice;

private:
	/**
	 * \brief A map between a time and a list of messages
	 */
	typedef QMap< double, QList <QSharedPointer<Packet> > > MessageList;

	double m_delay;								/**!< The delay */
	QSharedPointer<ErrorModel> m_errorModel;	/**!< The error model */
	QMap<quint32, NetDevice*> m_devices;		/**!< The list of attached NetDevices */
	MessageList m_messages;						/**!< Message list */
};
