/**
  * Copyright TSS 2017
  *
  */
#pragma once

#include "ADynamicAPI.h"
#include "ADynamicAPISetup.h"
#include "V2XFrameworkUtil.h"
#include "V2XIntersection.h"
#include <QObject>
#include <QMap>

#include <GKGeoUtil.h>

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
 * \see V2XFrameworkSetup
 */

/**
 * \brief Setup common types and attributes for the V2XFramework
 *
 * It creates the type for the network group, named internally by the
 * method V2XFramework::getInternalNetworkGroupName, which has supertype
 * "GKSectionObject".
 *
 * Then creates the type for the access point, named internally by the method
 * V2XFramework::getInternalAPName(), which has supertype "GKCircle".
 *
 * Then creates the attribute "connected_nodes" (complete name:
 * V2XFramework::getInternalAPName() + "::connected_nodes"), a read-only attribute
 * to see to which nodes the access point is connected to.
 *
 * Then creates the attribute named internally V2XFramework::getInternalStationTypeName()
 * (complete name: V2XFramework::getInternalAPName() + "::" +
 * V2XFramework::getInternalStationTypeName()) and initialize it with the values
 * for the StationType enum.
 */
extern "C" V2XFRAMEWORKEXPORT void V2XFrameworkSetup( ADynamicAPISetup & setup);


/**
 * \ingroup V2XFramework
 * \brief Interface for a generic V2XFramework
 *
 * Each method represents a Callback which is called in specific moments
 * of the simulation. These are inherited from ADynamicAPI, except for
 * arrivalNewAP which is called from inside the init method. Right now,
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
 * Please remember to call its method init to correctly initialize the
 * type names and folders for the framework.
 *
 * \see V2XSimpleAP
 * \see ADynamicAPI
 */
class V2XFRAMEWORKEXPORT V2XFramework: public ADynamicAPI
{
	Q_DISABLE_COPY(V2XFramework)
public:

	/**
	 * \brief Constructor
	 *
	 * \param setup API setup function
	 */
	V2XFramework(ADynamicAPISetup &setup);

	virtual ~V2XFramework();

	/**
	 * \brief Called each time an access point is added in the GUI
	 * \param id unique ID of the access point
	 * \param obj an opaque pointer to the object
	 */
	virtual void arrivalNewAP ( quint32 id, GKObject *obj,
								V2XIntersectionList controls) = 0;
	/**
	 * \brief Get the internal Network group name
	 * \return "NetworkGUIGroup"
	 */
	static QString getInternalNetworkGroupName ();
	/**
	 * \brief Get the GUI version of the Network group name
	 * \return "Network GUI Group", translatable
	 */
	static QString getGuiNetworkGroupName ();
	/**
	 * \brief Get the internal access point name
	 * \return "NetworkGUIAP"
	 */
	static QString getInternalAPName ();
	/**
	 * \brief Get the GUI version of the access point name
	 * \return "Network Access Point", translatable
	 */
	static QString getGuiAPName ();
	/**
	 * \brief Get the internal access point layer name
	 * \return "Access Points"
	 */
	static QString getInternalAPLayerName ();
	/**
	 * \brief Get the GUI version of the access point layer name
	 * \return "Access Points"
	 */
	static QString getGuiAPLayerName ();
	/**
	 * \brief Get the internal access point folder name
	 * \return "GKModel::top::infrastructure::accessPoints"
	 */
	static QString getInternalAPFolderName ();
	/**
	 * \brief Get the GUI version of the access point folder name
	 * \return "Access Points", translatable
	 */
	static QString getGuiAPFolderName ();

	/**
	 * \brief Get the internal framework name
	 * \return "V2XFramework"
	 */
	static QString getInternalFrameworkName ();

	/**
	 * \brief Get the internal name for the station type attribute
	 * \return "station_type"
	 */
	static QString getInternalStationTypeName ();

protected:
	/**
	 * \brief Initialize the class. It is obligatory to call it in the subclasses.
	 */
	void init ();

protected:
	ADynamicAPISetup m_setup; /**!< The setup object */
};


