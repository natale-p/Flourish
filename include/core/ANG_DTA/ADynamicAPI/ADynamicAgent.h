//-*-Mode: C++;-*-
#pragma once

#include "../DTAUtil.h"


//---- ADynamicAgent -----------------------------------------------------------
/*! The objective of this class is to get and set information to the vehicle every simulation step or simulation event.

	The user must rewrite its two virtual methods as:
	- The getState method will be called by Aimsun simulator for every simulation step.
	  No order of call is guaranty between different updates.
	- The setState method will be called by Aimsun simulator for every simulation step.
	  No order of call is guaranty between different updates.
*/
class DTAEXPORT ADynamicAgent
{
public:
	ADynamicAgent( unsigned short idhandler, void * anAgent );
	virtual ~ADynamicAgent();


	/*!  getState method will be called by Aimsun simulator for every simulation step
		*/
	virtual void getState(double time, double timeSta) = 0;

	/*!  setState method will be called by Aimsun simulator for every simulation step
		*/
	virtual void setState(double time, double timeSta) = 0;



	/*!  getId() returns the Aimsun id vehicle assigned during the simulation
		*/
	int getId() const;

	/*!  getVehType() returns the Aimsun Vehicle Type of the vehicle
		*/
	int getVehType() const;

	/*!  getLength() returns the length of the vehicle (meters)
		*/
	double getLength() const;

	/*!  getWidth() returns the width of the vehicle (meters)
		*/
	double getWidth() const;

	/*!  getMaxAcceleration() returns the Maximum acceleration of the vehicle as specified in the vehicle type considering local variations (m/s2)
		*/
	double getMaxAcceleration( ) const;

	/*!  getNormalDeceleration() returns the Nomal deceleration of the vehicle as specified in the vehicle type considering local variations (m/s2)
		*/
	double getNormalDeceleration( ) const;

	/*!  getMaxDeceleration() returns the Maximum (emergency) deceleration of the vehicle as specified in the vehicle type considering local variations (m/s2)
		*/
	double getMaxDeceleration( ) const;

	/*!  getClearance() returns the clearance space (Minimum gap) of the vehicle as defined in the vehicle type (m)
		*/
	double getClearance() const;

	/*!  getSensitivityFactor() returns the sensitivity Factor to Leader´s deceleration as defined in the vehicle type
		*/
	double getSensitivityFactor() const;

	/*!  getMinimumHeadway() returns the Minimum Headway (also know as Gap) in font of the vehicle as defined in the vehicle type (s)
		*/
	double getMinimumHeadway() const;


	/*!  getCoordinates() returns the coordinates of the midle front point and midle back point
		*/
	bool getCoordinates( double *xfront, double *yfront, double *zfront, double *xback, double *yback, double *zback) const;

	/*!  getFreeFlowSpeed() returns the maximum Desired Speed of the vehicle for the current lane (m/s)
		*/
	double getFreeFlowSpeed() const;

	/*!  getSpeed() returns the current speed of the vehicle (m/s)
		*/
	double getSpeed() const;

	/*!  getAcceleration() returns the current acceleration/deceleration of the vehicle (m/s2)
		*/
	double getAcceleration() const;

	/*!  getHeading() returns the heading express in angle : 0 Notrh, 90 East, 180 South 270 West
		*/

	double getHeading() const;

private:
	class Private;
	Private	*d;
};

