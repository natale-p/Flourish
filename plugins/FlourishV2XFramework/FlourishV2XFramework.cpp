#include "FlourishV2XFramework.h"
#include "FlourishConnectedAgent.h"
#include "FlourishVehicleRulesEngine.h"
#include "NetworkGUIAP.h"
#include "GKObject.h"

static int latencyColumn = 0;
static int probabilityLostPacketsColumn = 0;

void FlourishV2XFrameworkSetup( ADynamicAPISetup & setup )
{
	qDebug(" ...................................CALLING FlourishV2XFrameworkSetup");
	latencyColumn = setup.getColumn( "LatencyColumn" );
	if( latencyColumn == 0 ){
		latencyColumn = setup.addColumn( "LatencyColumn" , "Latency Mean Broker");
	}

	probabilityLostPacketsColumn = setup.getColumn( "ProbabilityLose" );
	if( probabilityLostPacketsColumn == 0 ){
		probabilityLostPacketsColumn = setup.addColumn( "ProbabilityLose" , "ProbabilityLose Broker");
	}
}

ADynamicAPI * FlourishV2XFrameworkFactory(ADynamicAPISetup & setup)
{
	return new FlourishV2XFramework(setup);
}

FlourishV2XFramework::FlourishV2XFramework(ADynamicAPISetup & setup): V2XFramework(setup)
{
	double probabilityLostPackets = setup.getExperimentValue(probabilityLostPacketsColumn);
	qDebug(" FlourishV2XFramework::FlourishV2XFramework()   "
		   "probabilityLostPackets = %f", probabilityLostPackets);
	double latency = setup.getExperimentValue(latencyColumn);
	qDebug(" FlourishV2XFramework::FlourishV2XFramework()   "
		   "latency = %f", latency);

	m_broker.setLatency(latency);
	m_broker.setProbLostPackets(probabilityLostPackets);

	QList<GKObject*> accessPoints = setup.getAccessPoints();

	for (GKObject *obj : accessPoints) {
		NetworkGUIAP *accessPoint = dynamic_cast<NetworkGUIAP*> (obj);
		if (accessPoint != 0) {
			m_broker.addStation(accessPoint->getId(), accessPoint->getPosition(),
								accessPoint->getRadius());
		}
	}
}

FlourishV2XFramework::~FlourishV2XFramework()
{
}

ADynamicAgent * FlourishV2XFramework::arrivalNewVehicle(unsigned short idHandler, void *agent)
{
	QPointer<FlourishConnectedAgent> res = new FlourishConnectedAgent (idHandler, agent, &m_broker);
	m_broker.addAgent (res);
	return res;
}

void FlourishV2XFramework::removedVehicle(unsigned short idHandler, ADynamicAgent * agent )
{
	Q_UNUSED(idHandler);
	FlourishConnectedAgent *ag = dynamic_cast<FlourishConnectedAgent*> (agent);
	if (ag != nullptr)
		m_broker.removeAgent(ag);
	delete agent;
}

void FlourishV2XFramework::preUpdate(double time, double timeSta, double simStep)
{
	m_broker.doPre(time, timeSta, simStep);
}

void FlourishV2XFramework::postUpdate(double time, double timeSta, double simStep)
{
	m_broker.doPost(time, timeSta, simStep);
}
