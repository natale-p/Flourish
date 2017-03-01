//-*-Mode: C++;-*-
#pragma once

#include "ADynamicAPI.h"
#include "ADynamicAPISetup.h"
#include "V2XBroker.h"
#include "VehicleRulesEngine.h"
#include "V2XFrameworkUtil.h"

class V2XFRAMEWORKEXPORT V2XFramework: public ADynamicAPI
{
public:
	V2XFramework(ADynamicAPISetup &setup);
	virtual ~V2XFramework();


	/*! Creates a new vehicle.
		*/
	virtual ADynamicAgent * arrivalNewVehicle( unsigned short idHandler, void *agent) = 0;

	/*! It is called whenever a vehicle exits the system.
		*/
	virtual void removedVehicle( unsigned short idHandler, ADynamicAgent * agent ) = 0;

	virtual void preUpdate(double time, double timeSta, double simStep) = 0;
	virtual void postUpdate(double time, double timeSta, double simStep) = 0;

protected:
	V2XBroker *broker;
	VehicleRulesEngine * ruleEngineItem;

};


