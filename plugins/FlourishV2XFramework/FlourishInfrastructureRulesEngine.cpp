/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#include "FlourishInfrastructureRulesEngine.h"
#include "FlourishAP.h"

FlourishInfrastructureRulesEngine::FlourishInfrastructureRulesEngine(): V2XRulesEngine()
{

}


FlourishInfrastructureRulesEngine::~FlourishInfrastructureRulesEngine()
{

}


void FlourishInfrastructureRulesEngine::evaluate( const QSharedPointer<const CAMMessage> &message,
												  V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	Q_UNUSED(agent);

	qDebug() << agent->getId() << "Received CAMMessage from" << message->getSource();
}

void FlourishInfrastructureRulesEngine::evaluate( const QSharedPointer<const DENMMessage> &message,
												  V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	Q_UNUSED(agent);



	qDebug() << agent->getId() << "Received DENMMessage from" << message->getSource();
}

void FlourishInfrastructureRulesEngine::evaluate( const QSharedPointer<const SPATEMMessage> &message,
												  V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	Q_UNUSED(agent);


	qDebug() << agent->getId() << "Received SPATEMMessage from" << message->getSource();
}

void FlourishInfrastructureRulesEngine::evaluate( const QSharedPointer<const MAPEMMessage> &message,
												  V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	Q_UNUSED(agent);


	qDebug() << agent->getId() << "Received MAPEMMessage from" << message->getSource();
}
