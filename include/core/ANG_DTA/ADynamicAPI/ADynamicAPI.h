/**
  * Copyright TSS 2017
  *
  */
#pragma once

#include "ADynamicAPIUtil.h"
#include "ADynamicAgent.h"
#include "ADynamicAPISetup.h"

class ADynamicAPI;
class DTAVeh;

typedef ADynamicAPI * (*ADynamicAPIFactory)(ADynamicAPISetup & setup);
typedef void (*ADynamicAPISetupCall)(ADynamicAPISetup &);

/**
  *
  * \defgroup ADynamicAPI A dynamic API for Aimsun
  *
  * This framework is independent from micro/meso/....
  * **TODO** To fill
  */

/**
  * \ingroup ADynamicAPI
  *
  * \brief A communication framework between Aimsun and an external plugin.
  *
  * The objective of this class is to manage the communication between
  * Aimsun simulator and this framework.
  *
  * The user must rewrite its four virtual methods, which acts as a callbacks
  * (the simulator will call these methods, and will use its return value).
  *
  * For a detailed description, please look at the documentation of each
  * method.
  *
  * \see arrivalNewVehicle
  * \see removedVehicle
  * \see preUpdate
  * \see postUpdate
  */
class ADYNAMICAPIEXPORT ADynamicAPI
{
	Q_DISABLE_COPY(ADynamicAPI)
public:

	/**
	 * \brief ADynamicAPI Constructor
	 *
	 * The ADynamicAPISetup will always be valid (a copy can be made)
	 *
	 * \param setup The API setup interface
	 */
	ADynamicAPI(ADynamicAPISetup &setup) { Q_UNUSED(setup); }

	/**
	 * \brief Deconstructor
	 */
	virtual ~ADynamicAPI() { }

	/**
	 * \brief A vehicle enters the system
	 *
	 * It is called whenever a vehicle enters inside the system and should create a new vehicle.
	 * \param idHandler Unique ID of the agent (it is equivalent to ADynamicAgent::getId)
	 * \param agent An opaque pointer representing the vehicle.
	 *
	 * \return A pointer to an ADynamicAgent to be used by the simulator
	 *
	 * An user outside Aimsun should never use this pointer directly.
	 */
	virtual ADynamicAgent * arrivalNewVehicle( quint32 idHandler, DTAVeh *agent) = 0;

	/**
	 * \brief A vehicle leaves the system
	 *
	 * It is called when a vehicle leaves the system; the memory pointed by
	 * agent can be safely freed.
	 *
	 * \param idHandler Unique ID of the agent
	 * \param agent The agent pointer
	 *
	 */
	virtual void removedVehicle( quint32 idHandler, ADynamicAgent * agent ) = 0;

	/**
	 * \brief Called before every simulation step (or simulation event)
	 * \param time To fill
	 * \param timeSta To fill
	 * \param simStep To fill
	 */
	virtual void preUpdate(double time, double timeSta, double simStep) = 0;
	/**
	 * \brief Called after every simulation step (or simulation event)
	 * \param time To fill
	 * \param timeSta To fill
	 * \param simStep To fill
	 */
	virtual void postUpdate(double time, double timeSta, double simStep) = 0;

};
