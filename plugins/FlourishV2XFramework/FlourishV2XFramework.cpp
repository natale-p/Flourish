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
	GKPreferencesGroup *prefs = setup.createPreferenceGroup("FlourishV2XFramework",
															QObject::tr("Flourish V2X plugin"));
	ADynamicAPISetup::UserPreference pref;


	QString delayGuiName = QObject::tr("Access Point propagation delay (s)");
	ret = setup.addTypeColumn(V2XFramework::getInternalAPName(),
							  "FlourishV2XFramework::delay",
							  delayGuiName,
							  ADynamicAPISetup::Double);
	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);

	pref.guiName = delayGuiName;
	pref.internalName = FlourishV2XFramework::getInternalAPDelayPreferenceName();
	pref.type = ADynamicAPISetup::Double;
	pref.defaultValue = "0.010";
	setup.createPreference(prefs, pref);

	QString apPERGuiName = QObject::tr("Access Point error rate (PER %)");

	ret = setup.addTypeColumn(V2XFramework::getInternalAPName(),
							  "FlourishV2XFramework::error_rate",
							  apPERGuiName,
							  ADynamicAPISetup::Double);
	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);

	pref.guiName = apPERGuiName;
	pref.internalName = FlourishV2XFramework::getInternalAPErrorRatePreferenceName();
	pref.type = ADynamicAPISetup::Double;
	pref.defaultValue = "0.000001";
	setup.createPreference(prefs, pref);

	QString agentGuiDelay = QObject::tr("Agent propagation delay (s)");
	ret = setup.addTypeColumn("GKMobileAgent",
							  "FlourishV2XFramework::delay",
							  agentGuiDelay,
							  ADynamicAPISetup::Double);
	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);


	pref.guiName = agentGuiDelay;
	pref.internalName = FlourishV2XFramework::getInternalAgentDelayPreferenceName();
	pref.type = ADynamicAPISetup::Double;
	pref.defaultValue = "0.020";
	setup.createPreference(prefs, pref);

	QString agentPERGuiName = QObject::tr("Agent packet error rate (PER %)");
	ret = setup.addTypeColumn("GKMobileAgent",
							  "FlourishV2XFramework::error_rate",
							  agentPERGuiName,
							  ADynamicAPISetup::Double);
	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);

	pref.guiName = agentPERGuiName;
	pref.internalName = FlourishV2XFramework::getInternalAgentErrorRatePreferenceName();
	pref.type = ADynamicAPISetup::Double;
	pref.defaultValue = "0.000001";
	setup.createPreference(prefs, pref);

	QString agentRadiusGuiName = QObject::tr("Agent radius (m)");
	ret = setup.addTypeColumn("GKMobileAgent",
							  "FlourishV2XFramework::radius",
							  agentRadiusGuiName,
							  ADynamicAPISetup::Double);
	Q_ASSERT (ret != -1);
	Q_UNUSED (ret);

	pref.guiName = agentRadiusGuiName;
	pref.internalName = FlourishV2XFramework::getInternalAgentRadiusPreferenceName();
	pref.type = ADynamicAPISetup::Double;
	pref.defaultValue = "15.0";
	setup.createPreference(prefs, pref);
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
										V2XIntersectionList controls)
{
	QPointer<FlourishAP> station = new FlourishAP (id, obj, m_setup);
	qDebug() << "Connecting to this ap" << controls.size() << "intersections";
	station->connectIntersections (controls);

	double delay = m_setup.getObjectValue<double>(obj, V2XFramework::getInternalAPName(),
												  "FlourishV2XFramework::delay");

	if (delay <= 0.0)
		delay = m_setup.getPreference( FlourishV2XFramework::getInternalAPDelayPreferenceName(), obj ).toDouble();

	double error_rate = m_setup.getObjectValue<double>(obj, V2XFramework::getInternalAPName(),
													   "FlourishV2XFramework::error_rate");
	if (error_rate <= 0.0)
		error_rate = m_setup.getPreference( FlourishV2XFramework::getInternalAPErrorRatePreferenceName(), obj).toDouble();

	if (delay <= 0.0 || error_rate <= 0.0) {
		delete station;
		qWarning() << "Can't setup the station" << id << "because of error_rate or delay set to 0.";
	} else {
		m_broker.addAP(station, delay, error_rate);
	}
}

ADynamicAgent * FlourishV2XFramework::arrivalNewVehicle(quint32 idHandler, DTAVeh *agent)
{
	QPointer<FlourishConnectedAgent> res = new FlourishConnectedAgent (idHandler, agent, &m_broker, m_setup);

	double del = m_setup.getObjectValue<double>(res->getVehicleType(),
												"GKMobileAgent",
												"FlourishV2XFramework::delay");
	if (del <= 0.0)
		del = m_setup.getPreference( FlourishV2XFramework::getInternalAgentDelayPreferenceName(),
									 res->getVehicleType() ).toDouble();

	double err = m_setup.getObjectValue<double>(res->getVehicleType(),
												"GKMobileAgent",
												"FlourishV2XFramework::error_rate");
	if (err <= 0.0)
		err = m_setup.getPreference( FlourishV2XFramework::getInternalAgentErrorRatePreferenceName(),
									 res->getVehicleType() ).toDouble();

	double rad = m_setup.getObjectValue<double>(res->getVehicleType(),
												"GKMobileAgent",
												"FlourishV2XFramework::radius");
	if (rad <= 0.0)
		rad = m_setup.getPreference( FlourishV2XFramework::getInternalAgentRadiusPreferenceName(),
									 res->getVehicleType() ).toDouble();

	if (del <= 0.0 || err <= 0.0 || rad < 0.0) {
		qWarning() << "Can't setup the agent" << idHandler << "because of attributes set to 0.";
		delete res;
		return nullptr;
	} else {
		m_broker.addAgent (res, rad, del, err);
		return res;
	}
}

void FlourishV2XFramework::removedVehicle(quint32 idHandler, ADynamicAgent * agent )
{
	Q_UNUSED(idHandler);
	FlourishConnectedAgent *ag = dynamic_cast<FlourishConnectedAgent*> (agent);
	if (ag != nullptr)
		m_broker.removeAgent(ag);
	delete ag;
}

void FlourishV2XFramework::preUpdate(double time, double timeSta, double simStep)
{
	m_broker.doPre(time, timeSta, simStep);
}

void FlourishV2XFramework::postUpdate(double time, double timeSta, double simStep)
{
	m_broker.doPost(time, timeSta, simStep);
}
