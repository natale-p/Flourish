//-*-Mode: C++;-*-
#pragma once


#include "../DTAUtil.h"
#include "ADynamicAgent.h"
#include "ADynamicAPISetup.h"

class ADynamicAPI;

typedef ADynamicAPI * (*ADynamicAPIFactory)(ADynamicAPISetup & setup);
typedef void (*ADynamicAPISetupCall)(ADynamicAPISetup &);

//---- ADynamicAPI -----------------------------------------------------------

/*! The objective of this class is to manage the communication between Aimsun simulator and this framework.

	The user must rewrite its four virtual methods as:
	- The arrivalNewVehicle will create a new vehicle. Usually this method will return
	  not an instance of ADynamicAgent but an instance of a subclass of this class.
	- The removedVehicle method will be called by Aimsun simulatorwhen a vehicle exits the system.
	  Usually this method will remove not an instance of ADynamicAgent but an instance of a subclass of this class

*/
class DTAEXPORT ADynamicAPI
{
public:

	ADynamicAPI(ADynamicAPISetup &setup);
	virtual ~ADynamicAPI();

	/*! It is called whenever a vehicle enters inside the system and should create a new vehicle (ADynamicAgent).
		*/
	virtual ADynamicAgent * arrivalNewVehicle( unsigned short idHandler, void *agent) = 0;

	/*! It is called whenever a vehicle exits the system.
		*/
	virtual void removedVehicle( unsigned short idHandler, ADynamicAgent * agent ) = 0;

	/*! It is called every simulation step (or simulation event) before update all Aimsun objects.
		*/
	virtual void preUpdate(double time, double timeSta, double simStep) = 0;
	/*! It is called every simulation step (or simulation event) after update all Aimsun objects.
		*/
	virtual void postUpdate(double time, double timeSta, double simStep) = 0;

};
