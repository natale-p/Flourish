/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#include "FlourishBroker.h"
#include "FlourishAP.h"
#include "FlourishConnectedAgent.h"

#include <SimpleChannel.h>

uint qHash(const V2XNetworkNode* node)
{
	return qHash(node->getId());
}

FlourishBroker::FlourishBroker() : QObject ()
{
}

FlourishBroker::~FlourishBroker()
{
	qDeleteAll(m_stations);
}

void FlourishBroker::doPost(double time, double timeSta, double simStep)
{
	Q_UNUSED(time);
	Q_UNUSED(timeSta);
	Q_UNUSED(simStep);

	// PLEASE MANTAIN THE ORDER
	// before: updateLinks
	// then: distribute and send
	for (FlourishConnectedAgent *agent : m_agents.values())
	{
		agent->updateLinks();
	}

	for(V2XSimpleAP *station : m_stations.values())
	{
		station->distributeMessages();
		station->sendMessage();
	}

}

void FlourishBroker::doPre(double time, double timeSta, double simStep)
{
	Q_UNUSED(timeSta);
	Q_UNUSED(simStep);

	V2XNetworkTime currentTime;
	currentTime.fromSeconds(time);

	// post operation for stations
	for(V2XSimpleAP *station : m_stations.values())
	{
		station->setTime(currentTime);
	}

	for (FlourishConnectedAgent *agent : m_agents.values())
	{
		agent->setTime(currentTime);
	}
}

void FlourishBroker::addAgent(FlourishConnectedAgent *agent)
{
	//agent->getChannel()->setErrorModel(m_errorModel);
	m_agents.insert(agent);
}

void FlourishBroker::removeAgent(FlourishConnectedAgent *agent)
{
	m_agents.remove(agent);
}

void FlourishBroker::addStation (quint32 id, const GKPoint &position,
								 double radius, double delay, double prob)
{

	qDebug() << "Added STATION" << id << delay << prob;

	QPointer<FlourishAP> station = new FlourishAP (position);
	station->setRadius(radius);
	QSharedPointer<RateErrorModel> errorModel = QSharedPointer<RateErrorModel>(new RateErrorModel());
	errorModel->setUnit(RateErrorModel::ERROR_UNIT_PACKET);
	errorModel->setRate(prob);
	errorModel->enable();

	station->getChannel()->setErrorModel(errorModel);
	station->getChannel()->setDelay(delay);

	m_stations.insert(id, station);

}

QSet<V2XNetworkNode *> FlourishBroker::getNearestStations(const V2XSimpleAP *target) const
{
	Q_ASSERT(target != 0);
	QSet<V2XNetworkNode*> ret;
	for(V2XSimpleAP *other : m_stations.values())
	{
		//qDebug() << "Checking if " << target->getId() << "is in range of " << other->getId()
		//		 << "Distance between them:" << other->getPosition().distance(target->getPosition())
		//		 << "StationPos" << other->getPosition() << "AgentPos:" << target->getPosition();

		if (target->getId() != other->getId()
				&& other->getRadius() > 0.0
				&& other->agentIsInRadius(target)) {
			ret.insert(other);
		}
	}

	return ret;
}

QSet<V2XNetworkNode*> FlourishBroker::getNearestAgent(const V2XSimpleAP *station) const
{
	Q_ASSERT(station != 0);
	QSet<V2XNetworkNode*> ret;
	for(FlourishConnectedAgent *agent : m_agents)
	{
		if (station->getId() != dynamic_cast<V2XNetworkNode*>(agent)->getId()
			&& agent->agentIsInRadius(station)) {
			ret.insert(agent);
		}
	}

	return ret;
}
