//-*-Mode: C++;-*-
#pragma once

#include "V2XFramework.h"
#include "FlourishV2XFrameworkUtil.h"


class ConnectedAgent;


extern "C" FLOURISHV2XFRAMEWORKEXPORT ADynamicAPI * FlourishV2XFrameworkFactory( ADynamicAPISetup & setup );
extern "C" FLOURISHV2XFRAMEWORKEXPORT void FlourishV2XFrameworkSetup( ADynamicAPISetup & setup);

class FLOURISHV2XFRAMEWORKEXPORT FlourishV2XFramework: public V2XFramework
{
public:

FlourishV2XFramework(ADynamicAPISetup & setup);
virtual ~FlourishV2XFramework();


/*! Creates a new vehicle.
		*/
virtual ADynamicAgent * arrivalNewVehicle( unsigned short idHandler, void *agent);

/*! It is called whenever a vehicle exits the system.
		*/
virtual void removedVehicle( unsigned short idHandler, ADynamicAgent * agent );

virtual void preUpdate(double time, double timeSta, double simStep);
virtual void postUpdate(double time, double timeSta, double simStep);

};

