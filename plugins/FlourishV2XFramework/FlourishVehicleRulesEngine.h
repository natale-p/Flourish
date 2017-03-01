//-*-Mode: C++;-*-
#pragma once

#include "VehicleRulesEngine.h"

class FlourishConnectedAgent;

class FlourishVehicleRulesEngine: public VehicleRulesEngine
{
public:
	FlourishVehicleRulesEngine();

	virtual ~FlourishVehicleRulesEngine();

	virtual bool evaluate(ConnectedAgent * agent);
};
