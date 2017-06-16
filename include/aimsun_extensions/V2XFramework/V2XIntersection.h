/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once
#include "ADynamicControl.h"
#include "ADynamicAPISetup.h"

#include "SPAT.h"
#include "MapData.h"

#include <QSharedPointer>
#include <QList>
#include <QVector>

class GKNode;
class GKSection;
class V2XIntersection;
class V2XGenericLane;

/**
 * \ingroup V2XFramework
 * \brief A shared pointer to a V2XConnectedControl
 */
typedef QSharedPointer<V2XIntersection> V2XIntersectionPointer;
/**
 * \ingroup V2XFramework
 * \brief A list of shared V2XConnectedControl pointers
 */
typedef QList<V2XIntersectionPointer> V2XIntersectionList;

/**
 * \ingroup V2XFramework
 * \brief A representation of an intersection in the context of V2XFramework.
 *
 * In the context of V2X communications, the Road Side Units (RSU) are entities
 * that get information from the intersection(s) they are connected to and broadcast
 * them to the near vehicles. This class translates information from the Aimsun
 * world to the V2X world. This done through the filling of common structures,
 * that are defined by the ETSI standard.
 *
 * The intersection is strictly linked to a node, and can obtain information
 * from it.
 *
 * Reasoning in terms of the framework, the intersections are connections
 * between V2XGenericLane objects.
 *
 */
class V2XIntersection : ADynamicControl
{
public:
	/**
	 * \brief Constructor
	 * \param node Aimsun node
	 */
	V2XIntersection(GKNode *node);

	/**
	  * \brief Deconstructor
	  */
	~V2XIntersection ();

	// Low-level primitives

	/**
	 * \brief Get the id of the intersection
	 * \return the ID of the intersection
	 */
	quint32 getId() const;

	/**
	 * \brief Get the name of the intersection
	 * \return The name of the intersection
	 */
	QString getName() const;

	// The following are taken from IntersectionStatusObject definition of
	// ISO_TS_19091.asn specifications
	/**
	 * \brief Check if manual control is enabled
	 *
	 * Timing reported is per programmed values, etc. but person
	 * at cabinet can manually request that certain intervals are
	 * terminated early (e.g. green).
	 *
	 * \return true in case manual control is enabled, false otherwise
	 */
	bool isManualControlEnabled () const { return false; }
	/**
	 * \brief Check if the timing is stopped
	 *
	 * Definition by the standard: "And all counting/timing has stopped."
	 *
	 * \return true if the timing is stopped, false otherwise
	 */
	bool isStopTimeActivated () const { return false; }

	/**
	 * \brief Check if there are hardware failures
	 *
	 * Used to indicate any detected hardware failure
	 *
	 * \return true in case of hardware failure
	 */
	bool isFlashFailing () const { return false; }

	/**
	 * \brief Check if preempt is active
	 *
	 * \return true if preempt is active
	 */
	bool isPreemptActive () const { return false; }
	/**
	 * \brief Check if signal priority is active
	 *
	 * \return true if signal priority is active
	 */
	bool isSignalPriorityActive () const { return false; }

	/**
	 * \brief Check if the operation timings are fixed
	 *
	 * Schedule of signals is based on time only
	 * \return true if the timings are fixed
	 */
	bool isFixedTimeOperation () const { return true; }

	/**
	 * \brief Check if the operation mode depends on traffic
	 *
	 * Operation is based on different levels of traffic parameters
	 * (requests, duration of gaps or more complex parameters)
	 *
	 * \return true if the operation depends on traffic
	 */
	bool isTrafficDependentOperation () const { return false; }
	/**
	 * \brief Check if the control is in standby
	 *
	 * Controller: partially switched off or partially amber flashing
	 * \return true if the controller is in standby
	 */
	bool isStandbyOperation () const { return false; }

	/**
	 * \brief Check if there are problems
	 * Controller has a problem or failure in operation
	 * \return true if there are problems in the controller
	 */
	bool failureMode () const { return false; }

	/**
	 * \brief Check if the controller is off
	 * Controller is switched off
	 * \return true if the controller is off
	 */
	bool isOff () const { return false; }

	/**
	 * \brief Check if there are recent MAP messages
	 * Map revision with content changes
	 * \return true if recently MAP messages have been processed
	 */
	bool recentMAPMessageUpdate () const { return false; }

	/**
	 * \brief Check for changes in the lanes
	 *
	 * Change in MAP's assigned lanes used (lane changes), or
	 * changes in the active lane list description
	 * \return true if there are changes from the previous state
	 */
	bool recentChangeInMAPassignedLanesIDsUsed () const { return false; }

	/**
	 * \brief Check if there are valid MAP messages
	 *
	 * MAP (and various lanes indexes) not available
	 * \return true if there are no valid MAP messages
	 */
	bool noValidMAPisAvailableAtThisTime () const { return false; }

	/**
	 * \brief Check if the SPAT system is working
	 *
	 * SPAT system is not working at this time
	 * \return true if the SPAT system is not working
	 */
	bool noValidSPATisAvailableAtThisTime() const { return false; }

	// End of IntersectionStatusObject definition




	/**
	 * \brief Method to get an intersection state as per ISO TS 19091
	 * \param intersectionState The object to fill.
	 * \param setup ADynamicAPISetup instance to query information about control
	 * plans
	 * \param time the time at which the state should be get
	 * \return true in case of success
	 */
	bool getIntersectionState(IntersectionState *intersectionState, const ADynamicAPISetup &setup,
							  double time) const;

	/**
	 * \brief Get the IntersectionStatusObject as per ISO TS 19091
	 * \param intersectionStateObject The object to fill
	 * \return true in case of success
	 */
	bool getIntersectionStatusObject(IntersectionStatusObject_t *intersectionStateObject) const;
	/**
	 * \brief Method to get the movement phase
	 * \param [in] phaseState The MovementPhaseState_t object to fill
	 * \return true in case of success
	 */
	bool getMovementPhaseState (MovementPhaseState_t *phaseState) const;
	/**
	 * \brief getTimingsChangeDetails
	 * \param [in] timing the TimeChangeDetails to fill
	 * \return true in case of success
	 */
	bool getTimingsChangeDetails (TimeChangeDetails *timing) const;

	/**
	 * \brief Get the map data for this intersection
	 *
	 * \param mapData [in] the MapData_t structure to fill
	 * \return true in case of success
	 */
	bool getMapData (MapData_t *mapData) const;

	/**
	 * \brief Get the geometry of the intersection
	 * \param geometry the structure to create and fill (use free() to release memory)
	 * \return true in case of success
	 */
	bool getIntersectionGeometry (IntersectionGeometryList *geometry) const;

private:
	GKNode *m_node; //!< Node
};
