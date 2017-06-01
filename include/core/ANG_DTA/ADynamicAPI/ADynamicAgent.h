/**
  * Copyright TSS 2017
  *
  */
#pragma once

#include "ADynamicAPIUtil.h"

class DTAVeh;
class DTAVehicleType;

/** \brief Get and set information from/to the Aimsun objects (including vehicles)
 *
 * The two methods which are called in a middle of the simulation steps are:
 *
 * - The getState method, will be called by Aimsun simulator for every simulation step.
 *  No order of call is guaranty between different updates.
 *- The setState method, will be called by Aimsun simulator for every simulation step.
 *  No order of call is guaranty between different updates.
 *
 * The other methods are getters for various vehicle properties, and they
 * resolve to the internal agent in Aimsun.
*/
class ADYNAMICAPIEXPORT ADynamicAgent
{
	Q_DISABLE_COPY(ADynamicAgent)
public:
	/**
	 * \brief Constructor
	 * \param idhandler Unique id of the agent (equivalent to call getId)
	 * \param anAgent Opaque pointer for Aimsun agent
	 */
	ADynamicAgent( quint32 idhandler, DTAVeh * anAgent );

	/**
	 * \brief Deconstructor
	 */
	virtual ~ADynamicAgent();


	/**
	 * \brief will be called by Aimsun simulator for every simulation step
	 *
	 * \param time TODO
	 * \param timeSta TODO
	 */
	virtual void getState(double time, double timeSta) = 0;

	/**
	 * \brief will be called by Aimsun simulator for every simulation step
	 *
	 * \param time TODO
	 * \param timeSta TODO
	 */
	virtual void setState(double time, double timeSta) = 0;

	/**
	 * \return the Aimsun id vehicle assigned during the simulation
	 */
	int getId() const;

	/**
	 * \return the Aimsun Vehicle Type of the vehicle
	 */
	int getVehType() const;

	/*!  getLength() returns the length of the vehicle (meters)
		*/
	double getLength() const;

	/**
	 * \return the width of the vehicle (meters)
	 */
	double getWidth() const;

	/**
	 * \return the Maximum acceleration of the vehicle as specified in the vehicle type considering local variations (m/s2)
	 */
	double getMaxAcceleration( ) const;

	/**
	 * \return the Nomal deceleration of the vehicle as specified in the vehicle type considering local variations (m/s2)
	 */
	double getNormalDeceleration( ) const;

	/**
	 * \return the Maximum (emergency) deceleration of the vehicle as specified in the vehicle type considering local variations (m/s2)
	 */
	double getMaxDeceleration( ) const;

	/**
	 * \return the clearance space (Minimum gap) of the vehicle as defined in the vehicle type (m)
	 */
	double getClearance() const;


	/**
	 * \return the sensitivity Factor to Leader´s deceleration as defined in the vehicle type
	 */
	double getSensitivityFactor() const;

	/**
	 * \return  the Minimum Headway (also know as Gap) in font of the vehicle as defined in the vehicle type (s)
	 */
	double getMinimumHeadway() const;

	/**
	 * \param xfront TODO
	 * \param yfront TODO
	 * \param zfront TODO
	 * \param xback TODO
	 * \param yback TODO
	 * \param zback TODO
	 * \return the coordinates of the middle front point and middle back point
	 */
	bool getCoordinates( double *xfront, double *yfront, double *zfront,
						 double *xback, double *yback, double *zback ) const;

	/**
	 * \return the maximum Desired Speed of the vehicle for the current lane (m/s)
	 */
	double getFreeFlowSpeed() const;


	/**
	 * \return the current speed of the vehicle (m/s)
	 */
	double getSpeed() const;


	/**
	 * \return the current acceleration/deceleration of the vehicle (m/s2)
	 */
	double getAcceleration() const;

	/**
	 * \return the heading express in angle : 0 North, 90 East, 180 South 270 West
	 */
	double getHeading() const;

	/**
	 * \return the vehicle type
	 */
	DTAVehicleType* getVehicleType() const;

private:
	/**
	 * \brief Private impl class
	 */
	class Private;
	Private	*d; /**!< Private impl pointer */
};

