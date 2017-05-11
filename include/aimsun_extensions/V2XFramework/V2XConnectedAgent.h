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
 *
 */
class V2XFRAMEWORKEXPORT V2XConnectedAgent: public V2XSimpleAP, public ADynamicAgent
{
	Q_OBJECT
	Q_DISABLE_COPY(V2XConnectedAgent)

public:
	/**
	 * \brief Constructor
	 * \param idhandler TODO
	 * \param agent TODO
	 */
	V2XConnectedAgent(unsigned short idhandler, void *agent);

	/**
	  * \brief Deconstructor
	  */
	virtual ~V2XConnectedAgent();

	// inherit by ADynamicAgent
	virtual void getState(double time, double timeSta) Q_DECL_OVERRIDE;
	virtual void setState(double time, double timeSta) Q_DECL_OVERRIDE;

	/**
	 * \brief Try to update the active links
	 */
	void updateLinks();

public slots:
	// inherit by V2XSimpleAP
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
	QMap<quint32, V2XNetworkNode*> m_inRangeStations; /**!< List of in-range stations */
	QMap<quint32, V2XNetworkNode*> m_inRangeAgents; /**!< List of in-range agents */
};


