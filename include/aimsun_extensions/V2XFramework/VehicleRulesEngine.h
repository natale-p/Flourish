#ifndef VEHICLERULESENGINE_H
#define VEHICLERULESENGINE_H

#include "V2XFrameworkUtil.h"

class ConnectedAgent;

class V2XFRAMEWORKEXPORT VehicleRulesEngine
{
public:
	VehicleRulesEngine();

	virtual ~VehicleRulesEngine();

	virtual bool evaluate(ConnectedAgent * agent) = 0;
};



#endif // VEHICLERULESENGINE_H
