//-*-Mode: C++;-*-
#pragma once

#include "VehicleRulesEngine.h"

class FlourishConnectedAgent;

/**
 * \ingroup V2XFramework
 * @brief The FlourishVehicleRulesEngine class
 */
class FlourishVehicleRulesEngine: public VehicleRulesEngine
{
public:
	FlourishVehicleRulesEngine();

	virtual ~FlourishVehicleRulesEngine();

	virtual bool evaluate(ConnectedAgent * agent);
};
