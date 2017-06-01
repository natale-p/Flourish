/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#include "FlourishV2XFramework.h"
#include "FlourishConnectedAgent.h"
#include "FlourishVehicleRulesEngine.h"
#include "FlourishAP.h"

void FlourishV2XFrameworkSetup( ADynamicAPISetup & setup )
{
	V2XFrameworkSetup(setup);
	int ret;

	ret = setup.addTypeColumn(V2XFramework::getInternalAPName(),
							  "FlourishV2XFramework::delay",
							  QObject::tr("Access Point propagation delay (s)"),
							  ADynamicAPISetup::Double);

	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);

	ret = setup.addTypeColumn(V2XFramework::getInternalAPName(),
							  "FlourishV2XFramework::error_rate",
							  QObject::tr("Access Point error rate (PER %)"),
							  ADynamicAPISetup::Double);
	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);

	ret = setup.addTypeColumn("GKMobileAgent",
							  "FlourishV2XFramework::delay",
							  QObject::tr("Agent propagation delay (s)"),
							  ADynamicAPISetup::Double);
	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);
	ret = setup.addTypeColumn("GKMobileAgent",
							  "FlourishV2XFramework::error_rate",
							  QObject::tr("Agent packet error rate (PER %)"),
							  ADynamicAPISetup::Double);
	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);
	ret = setup.addTypeColumn("GKMobileAgent",
							  "FlourishV2XFramework::radius",
							  QObject::tr("Agent radius (m)"), ADynamicAPISetup::Double);
	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);
}

ADynamicAPI * FlourishV2XFrameworkFactory(ADynamicAPISetup & setup)
{
	return new FlourishV2XFramework(setup);
}

FlourishV2XFramework::FlourishV2XFramework(ADynamicAPISetup & setup): V2XFramework(setup)
{	
	init();
}

FlourishV2XFramework::~FlourishV2XFramework()
{
}

void FlourishV2XFramework::arrivalNewAP(quint32 id, GKObject *obj,
										V2XConnectedControlList controls)
{
	Q_UNUSED(id);
	QPointer<FlourishAP> station = new FlourishAP (obj);
	station->connectControls (controls);

	double delay = m_setup.getObjectValue<double>(obj, V2XFramework::getInternalAPName(),
												  "FlourishV2XFramework::delay");

	double error_rate = m_setup.getObjectValue<double>(obj, V2XFramework::getInternalAPName(),
													   "FlourishV2XFramework::error_rate");

	m_broker.addAP(station, delay, error_rate);
}

ADynamicAgent * FlourishV2XFramework::arrivalNewVehicle(quint32 idHandler, DTAVeh *agent)
{
	QPointer<FlourishConnectedAgent> res = new FlourishConnectedAgent (idHandler, agent, &m_broker);

	double del = m_setup.getObjectValue<double>(res->getVehicleType(),
												"GKMobileAgent",
												"FlourishV2XFramework::delay");
	double err = m_setup.getObjectValue<double>(res->getVehicleType(),
												"GKMobileAgent",
												"FlourishV2XFramework::error_rate");
	double rad = m_setup.getObjectValue<double>(res->getVehicleType(),
												"GKMobileAgent",
												"FlourishV2XFramework::radius");


	qDebug () << del << err << rad;
	m_broker.addAgent (res, rad, del, err);
	return res;
}

void FlourishV2XFramework::removedVehicle(quint32 idHandler, ADynamicAgent * agent )
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
