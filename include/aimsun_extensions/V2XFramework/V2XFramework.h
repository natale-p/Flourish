/**
  * Copyright TSS 2017
  *
  */
#pragma once

#include "ADynamicAPI.h"
#include "ADynamicAPISetup.h"
#include "V2XFrameworkUtil.h"
#include <QObject>

/**
 * \defgroup V2XFramework V2X Framework for Aimsun
 *
 * Documentation for the V2X Framework of Aimsun. The framework implement a
 * (simple) way to define a communication network between vehicles, and between
 * vehicles and infrastructures. The final objective is to be able to exchange
 * messages, and (hopefully) to be able to use the information included to
 * take decisions.
 *
 * The core of the framework is a dynamic API, initialized in the class
 * V2XFramework. Then, objects (such as vehicles, or stations) are added
 * dynamically to the model, in order to represent a set of fixed-position and mobile
 * stations which communicates.
 *
 * \see V2XFramework
 */

extern "C" V2XFRAMEWORKEXPORT void V2XFrameworkSetup( ADynamicAPISetup & setup);


/**
 * \ingroup V2XFramework
 * \brief Interface for a generic V2XFramework
 *
 * Each method represents a Callback which is called in specific moments
 * of the simulation. Right now, only vehicles are managed by this API, but the
 * plan for the future is to manage infrastructures as well. Right now,
 * the only way to communicate with the GUI is through the finished GKModel
 * when the simulation starts.
 *
 * Right now only one way to communicate exists, while it is planned to have
 * multiple way to carry on communications. This first and simple way is called
 * "Simple", and is described in the class V2XSimpleAP.
 *
 * Each object in this framework follows the pre and post rule: a pre method
 * is called before any simulation step, while a post method is called after a
 * simulation step has been done for all the objects.
 *
 * \see V2XSimpleAP
 */
class V2XFRAMEWORKEXPORT V2XFramework: public ADynamicAPI
{
public:
	/**
	 * \brief Constructor
	 *
	 * \param setup API setup function
	 */
	V2XFramework(ADynamicAPISetup &setup);

	virtual ~V2XFramework();

	static QString getInternalNetworkGroupName () { return "NetworkGUIGroup"; }
	static QString getGuiNetworkGroupName () { return QObject::tr( "Network GUI Group" ); }
	static QString getInternalAPName () { return "NetworkGUIAP"; }
	static QString getGuiAPName () { return QObject::tr("Network Access Point"); }
	static QString getInternalAPLayerName () { return "Access Points"; }
	static QString getGuiAPLayerName () { return QObject::tr( "Access Points" ); }
	static QString getInternalAPFolderName () { return "GKModel::top::infrastructure::accessPoints"; }
	static QString getGuiAPFolderName () { return QObject::tr( "Access Points" ); }

	/**
	 * \brief Called when a new vehicle has been created
	 *
	 * \param idHandler
	 * \param agent
	 */
	virtual ADynamicAgent * arrivalNewVehicle( unsigned short idHandler, void *agent) = 0;

	/**
	 * \brief Called when a vehicle exits the system
	 *
	 * \param idHandler
	 * \param agent
	 */
	virtual void removedVehicle( unsigned short idHandler, ADynamicAgent * agent ) = 0;

	/**
	 * \brief Called at start of a new simulation step
	 *
	 * \param time
	 * \param timeSta
	 * \param simStep
	 */
	virtual void preUpdate(double time, double timeSta, double simStep) = 0;

	/**
	 * \brief Called at end of a simulation step
	 *
	 * \param time
	 * \param timeSta
	 * \param simStep
	 */
	virtual void postUpdate(double time, double timeSta, double simStep) = 0;

protected:
	GKType* getAPType() const;

private:
	GKType *m_apType;
};


