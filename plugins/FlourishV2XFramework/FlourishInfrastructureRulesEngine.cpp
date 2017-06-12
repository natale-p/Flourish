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

	qDebug() << "Received CAMMessage";
}

void FlourishInfrastructureRulesEngine::evaluate( const QSharedPointer<const DENMMessage> &message,
												  V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	Q_UNUSED(agent);



	qDebug() << "Received DENMMessage";
}

void FlourishInfrastructureRulesEngine::evaluate( const QSharedPointer<const SPATEMMessage> &message,
												  V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	Q_UNUSED(agent);


	qDebug() << "Received SPATEMMessage";
}

void FlourishInfrastructureRulesEngine::evaluate( const QSharedPointer<const MAPEMMessage> &message,
												  V2XSimpleAP *agent)
{
	Q_UNUSED(message);
	Q_UNUSED(agent);


	qDebug() << "Received MAPEMMessage";
}
