/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include <QSet>
#include "V2XNetworkNode.h"
#include "ErrorModel.h"

#include "GKGeoUtil.h"

class V2XSimpleAP;
class FlourishConnectedAgent;

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
 * The coordination of pre and post actions is done through a Qt connection.
 * In fact, not all the vehicles want to perform pre/post actions (e.g., the
 * vehicles which does not move), while all the others can connect to the
 * prepareForPost or prepareForPre signal. Then, a cycle is performed
 * on the list of the agents and stations to execute the pre and post operations.
 *
 * \see getNearestStation
 * \see getNearestAgent
 *
 */
class FlourishBroker : public QObject
{
	Q_OBJECT
public:
	/**
	 * \brief Constructor
	 */
	FlourishBroker();
	/**
	 * \brief Deconstructor
	 */
	~FlourishBroker();

	// Disable copy and move operators
	FlourishBroker(FlourishBroker const &) = delete;
	void operator=(FlourishBroker const &x) = delete;
	FlourishBroker (FlourishBroker&& other) noexcept = delete;
	FlourishBroker& operator= (FlourishBroker&& other) = delete;

	// Interface to FlourishV2XFramework

	/**
	 * \brief ask the subscriber to do the post operations
	 * \param time TODO
	 * \param timeSta TODO
	 * \param simStep TODO
	 */
	void doPost(double time, double timeSta, double simStep);

	/**
	 * \brief ask the subscriber to do the pre operations
	 * \param time TODO
	 * \param timeSta TODO
	 * \param simStep TODO
	 */
	void doPre(double time, double timeSta, double simStep);

	/**
	 * \brief Creates a new FlourishAP
	 * \param id id of the station
	 * \param position position
	 * \param radius the station radius
	 */
	void addStation (quint32 id, const GKPoint &position, double radius);

	void setLatency (double latency);

	void setProbLostPackets(double prob);

	/**
	 * \brief Save the pointer of the agent inside an internal list
	 *
	 * \param agent created agent
	 */
	void addAgent (FlourishConnectedAgent *agent);

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
	double m_latency; /**!< Latency for all vehicles and stations */
	double m_probLostPackets; /**!< Probability that a packet goes lost */
	QSharedPointer<RateErrorModel> m_errorModel;
};
