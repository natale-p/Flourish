/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "ADynamicAgent.h"
#include "V2XFrameworkUtil.h"
#include "V2XSimpleAP.h"

/**
 * \ingroup V2XFramework
 * \brief Represents a connected vehicle (e.g., a mobile station) in the framework
 *
 * The vehicle position is given by the Aimsun simulator. In this framework,
 * it is managed the connection (and the disconnection) of the vehicle with others
 * vehicles/infrastructures. This is done in a very transparent way, equipping
 * the vehicle with an access point, that works like the V2XSimpleAP object.
 *
 * The only difference is that it should maintain a list of the in-range
 * vehicles and stations, because after each simulation step it is required
 * to update the active links through a call to the method updateLinks.
 *
 * \see updateLinks
 *
 */
class V2XFRAMEWORKEXPORT V2XConnectedAgent: public V2XSimpleAP, public ADynamicAgent
{
	Q_OBJECT
	Q_DISABLE_COPY(V2XConnectedAgent)
public:
	/**
	 * \brief Constructor
	 * \param idHandler Id of the agent (should be unique)
	 * \param agent Opaque pointer representing the agent inside Aimsun
	 */
	V2XConnectedAgent(quint32 idHandler, DTAVeh *agent);

	/**
	  * \brief Deconstructor
	  */
	virtual ~V2XConnectedAgent();

	// inherit by ADynamicAgent
	virtual void getState(double time, double timeSta) Q_DECL_OVERRIDE;
	virtual void setState(double time, double timeSta) Q_DECL_OVERRIDE;
	// inherit by V2XNetworkNode
	virtual V2XNetworkPoint getPosition() const Q_DECL_OVERRIDE;

	/**
	 * \brief Try to update the active links
	 */
	void updateLinks();

public slots:
	/**
	 * \brief An AP has been removed
	 *
	 * This can be called because a AP we were connected to is being
	 * destroyed (e.g., it is leaving the network).
	 *
	 * \param station AP which is about to be removed
	 */
	virtual void stationRemoved(V2XSimpleAP *station) Q_DECL_OVERRIDE;

protected:
	/**
	 * \brief Get a set of station near the given station
	 *
	 * \param target target station
	 * \return a set of station for which the given position is in the communication range
	 */
	virtual QSet<V2XNetworkNode*> getNearestStations(const V2XNetworkNode *target) const = 0;

	/**
	 * \brief Get a set of agent near the given station
	 *
	 * \param station station
	 * \return a set of agents for which the given position is in the communication range
	 */
	virtual QSet<V2XNetworkNode*> getNearestAgent(const V2XNetworkNode *station) const = 0;

private:
	/**
	 * \brief Insert station into the appropriate list of in range stations/agents
	 * \param station Station to attach to
	 */
	virtual void connectTo(V2XSimpleAP *station);
	/**
	 * \brief check the list for any station out of range
	 * \param inRange list of stations or agents
	 */
	void checkForDisconnect(QMap<quint32, V2XNetworkNode*> *inRange);
	/**
	 * \brief Perform an initial search between all stations to find the in-range ones
	 */
	void initialConnect();

private:
	V2XNetworkPoint m_position; //!< The position of the station
	QMap<quint32, V2XNetworkNode*> m_inRangeStations; //!< List of in-range stations
	QMap<quint32, V2XNetworkNode*> m_inRangeAgents; //!< List of in-range agents
};


