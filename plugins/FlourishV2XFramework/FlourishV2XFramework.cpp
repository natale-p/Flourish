#include "FlourishV2XFramework.h"

#include "FlourishConnectedAgent.h"
#include "FlourishVehicleRulesEngine.h"
#include "FlourishV2XBroker.h"

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


	double latencyBroker = setup.getExperimentValue(latencyColumn);
	double alatencyTimeDev = 0.0;
	double alatencyTimeMin = latencyBroker - 1;
	double alatencyTimeMax = latencyBroker + 1;
	double probabilityLostPackets = setup.getExperimentValue(probabilityLostPacketsColumn);


	qDebug(" FlourishV2XFramework::FlourishV2XFramework()   latencyBroker = %f probabilityLostPackets = %f", latencyBroker, probabilityLostPackets);

	// it creates the context: broker and VehRulesEngine
	broker = new FlourishV2XBroker();
	((FlourishV2XBroker *)broker)->setParam(latencyBroker, alatencyTimeDev, alatencyTimeMin, alatencyTimeMax, probabilityLostPackets);

	ruleEngineItem=  new FlourishVehicleRulesEngine() ;
}

FlourishV2XFramework::~FlourishV2XFramework()
{
}

ADynamicAgent * FlourishV2XFramework::arrivalNewVehicle(unsigned short idHandler, void *agent)
{
	FlourishConnectedAgent *res = new FlourishConnectedAgent(idHandler,agent, ruleEngineItem, broker);
	return res;
}

void FlourishV2XFramework::removedVehicle(unsigned short idHandler, ADynamicAgent * agent )
{
	delete agent;
}

void FlourishV2XFramework::preUpdate(double time, double timeSta, double simStep)
{
	if (broker){
		broker->preUpdate(time, timeSta, simStep);
	}
}

void FlourishV2XFramework::postUpdate(double time, double timeSta, double simStep)
{
	if (broker){
		broker->postUpdate(time, timeSta, simStep);
	}
}

