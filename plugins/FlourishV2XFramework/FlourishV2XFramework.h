/**
  * Copyright TSS 2017
  *
  */
#pragma once

#include "V2XFramework.h"
#include "FlourishV2XFrameworkUtil.h"
#include "FlourishBroker.h"

/**
 * \defgroup FlourishV2X Flourish V2X Plugin
 *
 * The framework (based on V2XFramework) aims to provide a platform to simulate communications between
 * vehicles and between vehicles and stations. In the following, we will
 * refer to "core" as everything inside Aimsun simulator, keeping a distinction
 * between what is going on in this plugin and inside Aimsun.
 *
 * In the framework we have two main objects: a FlourishConnectedAgent, which
 * represents a vehicle, and FlourishAP, which represents a static
 * infrastructure. To enable V2V communication, each vehicle has internally
 * a station. This means that a FlourishConnectedAgent can be seen as a
 * moving station. Therefore, we can say that the main components of the framework
 * are mobile stations (FlourishConnectedAgent) and fixed stations (FlourishAP).
 *
 * Visually, in the Aimsun simulator, two main attributes are added to vehicles
 * and access point: delay and error_rate. Delay (in seconds) is the propagation
 * delay of the associated channel; error_rate is, instead, the probability
 * of losing a packet, expressed in %.
 *
 * They can be changed through the associated type (e.g., for access point
 * right click on the access point, and then go to "Attribute" tab, for Vehicles
 * go in Demand Data - Vehicle - and then right click on the vehicle class, and
 * then go to "Attribute" tab).
 *
 * To learn about the internals, look at the documentation of the FlourishV2XFramework class.
 *
 * \see FlourishV2XFramework
 */

extern "C" FLOURISHV2XFRAMEWORKEXPORT ADynamicAPI * FlourishV2XFrameworkFactory( ADynamicAPISetup & setup );
extern "C" FLOURISHV2XFRAMEWORKEXPORT void FlourishV2XFrameworkSetup( ADynamicAPISetup & setup);

/**
 * \ingroup FlourishV2X
 * \brief Main framework class
 *
 * The main objects of the plugin are created by this class, and in general
 * this is the door to the Aimsun simulator. It is based over the V2XFramework
 * class, so if you have not read it, it is better to start from there.
 *
 * The class is created at the beginning of the simulation and provides four
 * methods to exchange information with the core. We have:
 *
 * - arrivalNewVehicle, which is called by the core when a vehicle enters the scene;
 * - removedVehicle, which is called when a vehicle leaves the scene;
 * - preUpdate, which is called at the beginning of each simulation step;
 * - postUpdate, which is called at the end of each simulation step;
 *
 * The first two will be called independently from simulation steps, while
 * the last two will be called by the core each simulation step, depending
 * on the situation. The list of stations (or access point, the terms will be
 * used as synonyms in this framework).
 *
 * The stations are added at the beginning of the simulations, by querying
 * the simulation model; right now, moving or resizing infrastructures radius
 * during the simulation is not supported. The class in charge of saving a list
 * of stations and agents is FlourishBroker, and in its documentation you can
 * find the basics for the communication model.
 *
 * \see FlourishBroker
 * \see arrivalNewVehicle
 * \see preUpdate
 * \see postUpdate
 */
class FLOURISHV2XFRAMEWORKEXPORT FlourishV2XFramework: public V2XFramework
{
public:
	/**
	 * \brief FlourishV2XFramework constructor
	 * \param setup the API setup function
	 */
	FlourishV2XFramework(ADynamicAPISetup & setup);
	/**
	 * \brief Deconstructor
	 */
	virtual ~FlourishV2XFramework();

	// inherited from V2XFramework
	virtual ADynamicAgent * arrivalNewVehicle( quint32 idHandler, DTAVeh *agent) Q_DECL_OVERRIDE;
	virtual void removedVehicle( quint32 idHandler, ADynamicAgent * agent ) Q_DECL_OVERRIDE;
	virtual void preUpdate(double time, double timeSta, double simStep) Q_DECL_OVERRIDE;
	virtual void postUpdate(double time, double timeSta, double simStep) Q_DECL_OVERRIDE;
	virtual void arrivalNewAP (quint32 id, GKObject *obj, V2XIntersectionList controls) Q_DECL_OVERRIDE;

	/**
	 * \brief Get the internal name for the Access Point delay preference
	 * \return the specified name
	 */
	static QString getInternalAPDelayPreferenceName () { return "FlourishV2XFramework::Module::APDelay"; }
	/**
	 * \brief Get the internal name for the Access Point PER preference
	 * \return the specified name
	 */
	static QString getInternalAPErrorRatePreferenceName () { return "FlourishV2XFramework::Module::APPER"; }
	/**
	 * \brief Get the internal name for the Agent delay preference
	 * \return the specified name
	 */
	static QString getInternalAgentDelayPreferenceName () { return "FlourishV2XFramework::Module::AgentDelay"; }
	/**
	 * \brief Get the internal name for the Agent PER preference
	 * \return the specified name
	 */
	static QString getInternalAgentErrorRatePreferenceName () { return "FlourishV2XFramework::Module::AgentPER"; }
	/**
	 * \brief Get the internal name for the Agent radius preference
	 * \return the specified name
	 */
	static QString getInternalAgentRadiusPreferenceName () { return "FlourishV2XFramework::Module::AgentRadius"; }
private:
	FlourishBroker m_broker; //!< The broker */
};

