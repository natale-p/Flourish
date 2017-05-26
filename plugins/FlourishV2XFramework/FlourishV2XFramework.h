/**
  * Copyright TSS 2017
  *
  */
#pragma once

#include "V2XFramework.h"
#include "FlourishV2XFrameworkUtil.h"
#include "FlourishBroker.h"

class ConnectedAgent;


/**
 * \defgroup FlourishV2X Flourish V2X Plugin
 *
 * The framework aims to provide a platform to simulate communications between
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
 * To start, look at the documentation of the FlourishV2XFramework class.
 *
 * \see FlourishV2XFramework
 */

extern "C" FLOURISHV2XFRAMEWORKEXPORT ADynamicAPI * FlourishV2XFrameworkFactory( ADynamicAPISetup & setup );
extern "C" FLOURISHV2XFRAMEWORKEXPORT void FlourishV2XFrameworkSetup( ADynamicAPISetup & setup);

/**
 * \ingroup FlourishV2X
 * \brief Main framework class
 *
 *
 * The main objects of the plugin are created by this class, and in general
 * this is the door to the Aimsun simulator.
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
 *
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
	virtual ADynamicAgent * arrivalNewVehicle( unsigned short idHandler, void *agent);
	virtual void removedVehicle( unsigned short idHandler, ADynamicAgent * agent );
	virtual void preUpdate(double time, double timeSta, double simStep);
	virtual void postUpdate(double time, double timeSta, double simStep);
private:
	FlourishBroker m_broker; /**!< The broker pointer */
};

