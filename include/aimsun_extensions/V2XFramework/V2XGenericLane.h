/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once
#include "GenericLane.h"

#include <QList>
#include <QSharedPointer>

class GKNode;
class GKSection;
class V2XGenericLane;

/**
 * \ingroup V2XFramework
 * \brief A shared pointer to a V2XGenericLane
 */
typedef QSharedPointer<V2XGenericLane> V2XGenericLanePointer;
/**
 * \ingroup V2XFramework
 * \brief A list of shared V2XGenericLane pointers
 */
typedef QList<V2XGenericLanePointer> V2XGenericLaneList;

/**
 * \ingroup V2XFramework
 * \brief A generic lane connected to an intersection
 *
 * Through its public method, it can extract information from the Aimsun
 * simulator into common defined structures, to be used to construct ETSI-compliant
 * messages.
 */
class V2XGenericLane
{
private:
	/**
	 * \brief Constructor
	 *
	 * It is not possible to instantiate a V2XGenericLane; instead, use its
	 * static method to gather the information required.
	 *
	 * \param section The section (Aimsun naming) linked to this lane
	 */
	V2XGenericLane();
	/**
	 * \brief Deconstructor
	 */
	~V2XGenericLane();
public:
	// The following are taken from GenericLane definition of
	// ISO_TS_19091.asn specifications

	/**
	 * \brief Get the unique ID of the section (lane)
	 * \param section Section to gather the ID from
	 * \return the unique ID of the section
	 */
	static quint32 getId (const GKSection *section);

	/**
	 * \brief Fill a generic lane struct
	 *
	 * The method uses other public methods of this class to build
	 * a valid generic line struct to use in messages
	 *
	 * \param section Section to gather the information from
	 * \param node Node to get information on turnings / signals from
	 * \param genericLane struct to fill
	 * \return true if success
	 */
	static bool getGenericLane (const GKSection *section, const GKNode *node, GenericLane_t *genericLane);

	/**
	 * \brief Fill a ConnectsTo structure
	 *
	 * Indicates to which sections this lane connects to.
	 *
	 * \param section The reference section
	 * \param node The reference node
	 * \param connectsTo The structure to fill
	 * \return true if success
	 */
	static bool getConnectsTo (const GKSection *section, const GKNode *node, ConnectsToList_t *connectsTo);

	/**
	 * \brief Get lane attributes
	 *
	 * \param section Section to gather the information from
	 * \param attributes structure to fill
	 * \return true if success
	 */
	static bool getLaneAttributes(const GKSection *section, LaneAttributes_t *attributes);

	// For LaneAttributes_t
	/**
	 * \brief getDirectionalUse
	 * Allowed directions of travel in the lane object. All lanes
	 * are described from the stop line outwards.
	 *
	 * The bits are defined as: name [position] -> desc :
	 *
	 * - ingressPath     (0) -> travel from rear of path to front is allowed
	 * - egressPath      (1) -> travel from front of path to rear is allowed
	 *
	 * Notes:  No Travel, i.e. the lane object type does not support
	 * travel (medians, curbs, etc.) is indicated by not
	 * asserting any bit value. Bi-Directional Travel (such as a ped crosswalk) is
	 * indicated by asserting both of the bits
	 *
	 * \param section Section to gather the information from
	 * \param laneDirection structure to fill
	 *
	 * \return true if success
	 */
	static bool getDirectionalUse(const GKSection *section, LaneDirection_t *laneDirection);

	/**
	 * \brief Get the object this lane is shared with
	 *
	 * The bits are defined as follows:
	 *
	 * - overlappingLaneDescriptionProvided  (0) -> Assert when another lane object
	 * is present to describe the path of the overlapping shared lane. This construct
	 * is not used for lane objects which simply cross
	 * - multipleLanesTreatedAsOneLane       (1) -> Assert if the lane object path and width details represents
	 * multiple lanes within it that are not further described
	 *
	 * Various modes and type of traffic that may share this lane:
	 *
	 * - otherNonMotorizedTrafficTypes       (2) -- horse drawn etc.
	 * - individualMotorizedVehicleTraffic   (3)
	 * - busVehicleTraffic                   (4)
	 * - taxiVehicleTraffic                  (5)
	 * - pedestriansTraffic                  (6)
	 * - cyclistVehicleTraffic               (7)
	 * - trackedVehicleTraffic               (8)
	 * - pedestrianTraffic                   (9)
	 *
	 * All zeros would indicate 'not shared' and 'not overlapping'
	 *
	 * \param section Section to gather the information from
	 * \param laneSharing structure to fill
	 * \return true if success
	 */
	static bool getSharedWith(const GKSection *section, LaneSharing_t *laneSharing);

	/**
	 * \brief Get attributes for a vehicle lane type
	 *
	 * The bits are defined as follows:
	 *
	 * - isVehicleRevocableLane       (0) this lane may be activated or not based
	 * on the current SPAT message contents. If not asserted, the lane is ALWAYS present
	 * - isVehicleFlyOverLane         (1) path of lane is not at grade
	 * - hovLaneUseOnly               (2)
	 * - restrictedToBusUse           (3)
	 * - restrictedToTaxiUse          (4)
	 * - restrictedFromPublicUse      (5)
	 * - hasIRbeaconCoverage          (6)
	 * - permissionOnRequest          (7)e.g. to inform about a lane for e-cars
	 *
	 * \param section Section to gather the information from
	 * \param laneAttrVeh structure to fill
	 * \return true if success
	 */
	static bool getVehicleLaneType (const GKSection *section, LaneAttributes_Vehicle_t *laneAttrVeh);

	/**
	 * \brief Get the type of the lane, with its attributes
	 *
	 * There could be different type of lanes. Depending on the internal
	 * object, this function can return attributes for motor vehicle lanes,
	 * pedestrian crosswalks, bike lanes, pedestrian sidewalk paths,
	 * medians & channelization, roadway markings, trains and trolleys,
	 * parking and stopping lanes.
	 *
	 * \param section Section to gather the information from
	 * \param laneTypeAttributes struct to fill
	 * \return true if success
	 */
	static bool getLaneType(const GKSection *section, LaneTypeAttributes_t *laneTypeAttributes);
	// End For LaneAttributes_t

	/**
	 * \brief Get the lane nodes
	 *
	 * The structure can be defined as:
	 * - a lane made up of two or more XY node points and any attributes defined in those nodes
	 * - a lane path computed by translating the data defined by another lane
	 *
	 * \param section Section to gather the information from
	 * \param nodeList we return a lane made up by four XY node points representing
	 * the lane as a rectangle, using x and y in aimsun as latitude and longitude
	 * \return true if success
	 */
	static bool getNodeListXY(const GKSection *section, NodeListXY_t *nodeList);

	// END of specifications
};
