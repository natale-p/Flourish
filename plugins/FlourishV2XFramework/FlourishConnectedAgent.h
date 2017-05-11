/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "V2XConnectedAgent.h"

class FlourishBroker;

class FlourishConnectedAgent : public V2XConnectedAgent
{
public:
	FlourishConnectedAgent (unsigned short idhandler, void *agent, FlourishBroker *broker);
public slots:
	/**
	 * \brief A message has been received
	 * \param device Device which has received the message
	 * \param packet Packet received
	 * \param addr Source address
	 */
	virtual void received (const QPointer<NetDevice> &device,
						   const QSharedPointer<const Packet> &packet, const Address &addr);
protected:
	/**
	 * \brief Generate a single message to be transmitted
	 *
	 * \return A packet containing the message
	 */
	virtual QSharedPointer<Packet> generateMessage();

	/**
	 * \brief Get a set of station near the given station
	 *
	 * If the position are m, the cost of this function is O(m).
	 * \param target target station
	 * \return a set of station for which the given position is in the communication range
	 */
	QSet<V2XNetworkNode*> getNearestStations(const V2XNetworkNode *target) const;
	/**
	 * \brief Get a set of agent near the given station
	 *
	 * If the agents are n, the cost of this function is O(n).
	 * \param station station
	 * \return a set of agents for which the given position is in the communication range
	 */
	QSet<V2XNetworkNode*> getNearestAgent(const V2XNetworkNode *station) const;

private:
	FlourishBroker *m_broker;
};
