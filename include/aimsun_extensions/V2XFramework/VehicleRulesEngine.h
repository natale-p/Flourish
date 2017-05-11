#pragma once
#include "V2XFrameworkUtil.h"

class ConnectedAgent;

/**
 * \ingroup V2XFramework
 * \brief The VehicleRulesEngine class
 */
class V2XFRAMEWORKEXPORT VehicleRulesEngine
{
public:
	VehicleRulesEngine();

	virtual ~VehicleRulesEngine();

	virtual bool evaluate(ConnectedAgent * agent) = 0;
};
