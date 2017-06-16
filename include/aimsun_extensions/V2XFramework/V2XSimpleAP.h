/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "V2XNetworkNode.h"
#include "V2XIntersection.h"
#include "NetDevice.h"
#include "Packet.h"

class SimpleChannel;
class GKObject;

/**
 * \ingroup V2XFramework
 * \brief Represent a wireless Access Point
 *
 * The objective is to model any wireless object which has the capability to
 * send or to receive a message. The communication model lacks
 * propagation fading, transmission power, and in general, is a very basic one.
 *
 * <b> Features </b>
 *
 * A radius is the main property of a wireless access point, to emulate a
 * propagation fading. Every object out of this radius is, therefore, unable
 * to communicate with it (take a look to setRadius and getRadius, and for
 * connectivity, to the method agentIsInRadius).
 *
 * A channel (method getChannel) characterizes each access point; it is the
 * medium through with it can send and receive messages. There are as many
 * channels as access points (contrary on the real world in which the number
 * of channels is often limited). The documentation of SimpleChannel defines
 * the properties of the channel itself (namely, ErrorModel and latency).
 *
 * <b> Communication Model </b>
 *
 * The access point is born to be passive, in the sense that it does not
 * initiate any connection, but instead is waiting passively for others
 * to connect to its channel (we will refer to these others as subscribers).
 * The user of this class is supposed to update the current time with the
 * method setTime of V2XNetworkNode. Then, it is expected to call the
 * methods distributeMessages() and sendMessage(). While the names of
 * the methods are similar, their operations differ.
 *
 * \see distributeMessages
 * \see sendMessages
 *
 */
class V2XFRAMEWORKEXPORT V2XSimpleAP : public V2XNetworkNode
{
	Q_OBJECT
	Q_DISABLE_COPY(V2XSimpleAP)

public:
	/**
	 * \brief Constructor for a moving AP
	 * \param id Unique ID for the object
	 */
	V2XSimpleAP (quint32 id);
	/**
	 * \brief Constructor for an AP
	 * \param id Unique ID for the object
	 * \param obj (Opaque) pointer to an object inside Aimsun
	 */
	V2XSimpleAP(quint32 id, const GKObject *obj);

	/**
	 * \brief Deconstructor
	 */
	~V2XSimpleAP ();

	/**
	 * \brief Set the radius of the AP
	 * \param radius Radius
	 */
	void setRadius (double radius);

	/**
	 * \brief Get the AP radius
	 * \return the AP radius
	 */
	double getRadius () const;

	/**
	 * \return The channel of this AP
	 */
	SimpleChannel* getChannel () const;

	/**
	 * \brief Instruct the channel to deliver the enqueued message
	 *
	 * The delivery will be done up to the current time.
	 *
	 * \see sendMessage
	 */
	void distributeMessages();

	/**
	 * \brief Generate, and then send to the device, a message
	 *
	 * The message is generated through the method generateMessage, and then
	 * it is sent with a broadcast address to the personal device.
	 * V2XSimpleAP is using the Simple communication framework, so to discover
	 * how a message is broadcasted, please take a look to the SimpleNetDevice
	 * documentation.
	 */
	void sendMessage();

	/**
	 * \brief Check if the given agent is in the radius of the AP
	 * \param agent Agent to check
	 * \return true if the agent in the range of the AP
	 */
	bool agentIsInRadius(const V2XNetworkNode *agent) const
	{
		GKPoint agentPos = agent->getPosition();
		return V2XSimpleAP::isInRadius(this, agentPos);
	}

	/**
	 * \brief Attach to this station a list of V2XIntersection objects.
	 *
	 * After this call, the station become a RSU.
	 *
	 * \param connectedIntersections The connected intersections
	 */
	void connectIntersections (V2XIntersectionList connectedIntersections);

	//inherited from V2XNetworkNode
	virtual GKPoint getPosition() const Q_DECL_OVERRIDE;

public slots:
	/**
	 * \brief A message has been received
	 * \param device Device which has received the message
	 * \param packet Packet received
	 * \param addr Source address
	 */
	virtual void received (const QPointer<NetDevice> &device,
						   const QSharedPointer<const Packet> &packet, const Address &addr) = 0;

	/**
	 * \brief A AP has been removed
	 *
	 * This can be called because a AP we were connected to is being
	 * destroyed (e.g., it is leaving the network).
	 *
	 * \param AP AP which is about to be removed
	 */
	virtual void stationRemoved (V2XSimpleAP *AP);

signals:
	/**
	 * \brief Signal emitted in the deconstructor, to signal that this AP
	 * is about to be removed from the network
	 *
	 * \param AP (this) AP
	 */
	void destroyed(V2XSimpleAP *AP);

protected:
	/**
	 * \brief Attach to the specified AP
	 * \param AP AP to attach to
	 */
	virtual void connectTo(V2XSimpleAP *AP);

	/**
	 * \brief Detach from the specified AP
	 *
	 * \param AP AP to detach
	 */
	virtual void disconnectFrom(V2XSimpleAP *AP);

	/**
	 * \brief Generate a list of messages to be transmitted
	 *
	 * \return A list of messages
	 */
	virtual PacketPointerList generateMessage() = 0;

protected:
	V2XIntersectionList m_connectedIntersections; //!< The list of intersections connected to this AP

private:
	/**
	 * \brief Check if the given position is in the radius of the AP
	 * \param AP AP to check
	 * \param pos Position to check
	 * \return true if pos in the range of the AP
	 */
	static bool isInRadius(const V2XSimpleAP *AP, const GKPoint &pos)
	{
		return (AP->getPosition().distance2D(pos) < AP->getRadius());
	}

private:
	QPointer<SimpleChannel> m_channel;	//!< Channel of the AP
	double m_radius;					//!< Radius of the AP
	QMap<quint32, QMetaObject::Connection> m_stationConnection; //!< Connection to the destroyed signal of other APs
	const GKObject *m_obj; //!< Associated object
};
