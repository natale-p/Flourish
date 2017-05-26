/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#include "FlourishV2XFramework.h"
#include "FlourishConnectedAgent.h"
#include "FlourishVehicleRulesEngine.h"
#include "NetworkGUIAP.h"
#include "GKType.h"
#include "GKColumn.h"
#include "GKObject.h"

void FlourishV2XFrameworkSetup( ADynamicAPISetup & setup )
{
	V2XFrameworkSetup(setup);
	qDebug() << "FlourishV2XFrameworkSetup    BEGIN";

	GKType *apType = setup.findType(V2XFramework::getInternalAPName());
	apType->addColumn(V2XFramework::getInternalAPName() + "::FlourishV2XFramework::delay",
					  QObject::tr("Access point propagation delay (s)"), GKColumn::Double);

	apType->addColumn("FlourishV2XFramework::error_rate",
					  QObject::tr("Access point packet error rate (PER %)"),
					  GKColumn::Double);

	GKType *vehType = setup.findType("GKMobileAgent");
	vehType->addColumn("FlourishV2XFramework::agent_delay",
					   QObject::tr("Agent propagation delay (s)"), GKColumn::Double);
}

ADynamicAPI * FlourishV2XFrameworkFactory(ADynamicAPISetup & setup)
{
	return new FlourishV2XFramework(setup);
}

FlourishV2XFramework::FlourishV2XFramework(ADynamicAPISetup & setup): V2XFramework(setup)
{
	QList<GKObject*> accessPoints = setup.getObjInFolder(setup.findFolder(V2XFramework::getInternalAPFolderName()));

	for (GKObject *obj : accessPoints) {
		NetworkGUIAP *accessPoint = dynamic_cast<NetworkGUIAP*> (obj);
		GKType *type = accessPoint->getType();
		Q_ASSERT(type != nullptr);

		GKColumn *delay = type->getColumn(V2XFramework::getInternalAPName() + "::FlourishV2XFramework::delay", GKType::eSearchOnlyThisType);
		GKColumn *error_rate = type->getColumn("FlourishV2XFramework::error_rate", GKType::eSearchOnlyThisType);

		Q_ASSERT(delay != nullptr);
		Q_ASSERT(error_rate != nullptr);

		if (accessPoint != 0) {
			m_broker.addStation(accessPoint->getId(), accessPoint->getPosition(),
								accessPoint->getRadius(), accessPoint->getDataValueDouble(delay),
								accessPoint->getDataValueDouble(error_rate));
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
