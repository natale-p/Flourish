/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once
#include "FlourishV2XFrameworkUtil.h"
#include "FlourishVehicleRulesEngine.h"
#include "V2XConnectedAgent.h"
#include "ADynamicAPISetup.h"

class FlourishBroker;

/**
 * \ingroup FlourishV2X
 * \brief A mobile agent
 *
 * When it receives a message, the method received is invoked, and then the
 * correspondent methods of FlourishVehicleRulesEngine are called. In particular,
 * right now are managed CAM, DENM, and SPATEM messages.
 *
 * To generate a message, use the method generateMessage, that should return
 * a list of messages to transmit.
 */
class FLOURISHV2XFRAMEWORKEXPORT FlourishConnectedAgent : public V2XConnectedAgent
{
public:
	/**
	 * \brief Constructor
	 * \param idhandler id of the agent
	 * \param agent opaque pointer to the agent
	 * \param broker the broker
	 * \param setup the API setup
	 */
	FlourishConnectedAgent (quint32 idhandler, DTAVeh *agent, FlourishBroker *broker,
							ADynamicAPISetup &setup);
public slots:
	/**
	 * \brief A message has been received
	 * \param device Device which has received the message
	 * \param packet Packet received
	 * \param addr Source address
	 */
	virtual void received (const QPointer<NetDevice> &device,
						   const QSharedPointer<const Packet> &packet, const Address &addr) Q_DECL_OVERRIDE;
protected:
	/**
	 * \brief Generate messages to be transmitted
	 *
	 * \return A list of messages
	 */
	virtual PacketPointerList generateMessage() Q_DECL_OVERRIDE;

	/**
	 * \brief Get a set of station near the given station
	 *
	 * If the position are m, the cost of this function is O(m).
	 * \param target target station
	 * \return a set of station for which the given position is in the communication range
	 */
	QSet<V2XNetworkNode*> getNearestStations(const V2XNetworkNode *target) const Q_DECL_OVERRIDE;
	/**
	 * \brief Get a set of agent near the given station
	 *
	 * If the agents are n, the cost of this function is O(n).
	 * \param station station
	 * \return a set of agents for which the given position is in the communication range
	 */
	QSet<V2XNetworkNode*> getNearestAgent(const V2XNetworkNode *station) const Q_DECL_OVERRIDE;

private:
	FlourishBroker *m_broker; /**!< Pointer to the broker */
	FlourishVehicleRulesEngine m_engine; /**!< Instance of the Veh Rules Engine */
	int m_stationType;
};
