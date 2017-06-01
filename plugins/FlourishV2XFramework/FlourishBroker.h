/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include <QSet>
#include "V2XNetworkNode.h"
#include "ErrorModel.h"
#include "FlourishV2XFrameworkUtil.h"

class V2XSimpleAP;
class FlourishConnectedAgent;
class FlourishAP;

extern uint qHash(const V2XNetworkNode* node);

/**
 * \ingroup FlourishV2X
 * \brief Supervise the framework operations
 *
 * The class is responsible to save pointers to all the stations and
 * agents in the simulation. Moreover, it coordinates the pre and post
 * events between all the stations.
 *
 * More in particular, the class provide a way to find nearest stations and
 * agents (with an high computational cost; calling n and m the number of vehicles
 * and stations, respectively, the cost is O(n) for retrieving the nearest agents
 * and O(m) to retrieve the nearest stations).
 *
 * We have different group of methods, meant to be called from different classes.
 * The first group (doPost, doPre, addStation, addAgent, removeAgent) is meant
 * to be called by FlourishV2XFramework. The second one, composed by now,
 * getNearestStation, getNearestAgent, is meant to be called by the stations.
 *
 * To see what is possible to do with the agents and stations, please take a
 * look to their documentation (FlourishConnectedAgent and FlourishAP).
 *
 * \see getNearestStation
 * \see getNearestAgent
 *
 */
class FLOURISHV2XFRAMEWORKEXPORT FlourishBroker : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(FlourishBroker)
public:
	/**
	 * \brief Constructor
	 */
	FlourishBroker();
	/**
	 * \brief Deconstructor
	 */
	~FlourishBroker();

	// Interface to FlourishV2XFramework

	/**
	 * \brief Ask the agents and stations to do the post operations
	 *
	 * The order is the following:
	 *
	 * - It is asked to all the agents to update their links, giving their
	 * positions and the positions of the other agent/stations
	 * - It is asked to all the agents and to all the stations to exchange
	 * messages, and then to generate their message to broadcast
	 *
	 * \param time TODO
	 * \param timeSta TODO
	 * \param simStep TODO
	 */
	void doPost(double time, double timeSta, double simStep);

	/**
	 * \brief Ask the agents and stations to do the pre operations
	 *
	 * It only update the current time in all the agents/stations. In the future,
	 * it will trigger the analysis of the income messages.
	 *
	 * \param time TODO
	 * \param timeSta TODO
	 * \param simStep TODO
	 */
	void doPre(double time, double timeSta, double simStep);

	/**
	 * \brief Creates a new FlourishAP
	 * \param ap Access Point
	 * \param delay the propagation delay of this station
	 * \param prob the probability of loss (PER) of this station
	 */
	void addAP (FlourishAP *ap, double delay, double prob);

	/**
	 * \brief Save the pointer of the agent inside an internal list
	 *
	 * \param agent created agent
	 * \param radius the radius of the agent
	 * \param delay the delay of its channel
	 * \param prob the error probability (PER)
	 */
	void addAgent (FlourishConnectedAgent *agent, double radius, double delay, double prob);

	/**
	 * \brief removeAgent
	 * \param agent
	 */
	void removeAgent (FlourishConnectedAgent *agent);

	// Interface to stations

	/**
	 * \brief Get a set of station near the given station
	 *
	 * If the position are m, the cost of this function is O(m).
	 * \param target target station
	 * \return a set of station for which the given position is in the communication range
	 */
	QSet<V2XNetworkNode*> getNearestStations(const V2XSimpleAP *target) const;
	/**
	 * \brief Get a set of agent near the given station
	 *
	 * If the agents are n, the cost of this function is O(n).
	 * \param station station
	 * \return a set of agents for which the given position is in the communication range
	 */
	QSet<V2XNetworkNode*> getNearestAgent(const V2XSimpleAP *station) const;

private:
	QMap<quint32, V2XSimpleAP*> m_stations; /**!< All the stations in the simulation */
	QSet<FlourishConnectedAgent*> m_agents; /**!< All the agents in the simulation */

	QSharedPointer<RateErrorModel> m_agentModel; /**!< ErrorModel for agents */
};
