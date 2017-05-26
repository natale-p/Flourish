//-*-Mode: C++;-*-
#pragma once

#include "VehicleRulesEngine.h"
#include "FlourishV2XFrameworkUtil.h"

class FlourishConnectedAgent;

/**
 * \ingroup V2XFramework
 * @brief The FlourishVehicleRulesEngine class
 */
class FLOURISHV2XFRAMEWORKEXPORT FlourishVehicleRulesEngine: public VehicleRulesEngine
{
public:
	FlourishVehicleRulesEngine();

	virtual ~FlourishVehicleRulesEngine();

	virtual bool evaluate(ConnectedAgent * agent);
};
