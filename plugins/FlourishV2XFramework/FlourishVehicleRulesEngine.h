/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "V2XRulesEngine.h"
#include "FlourishV2XFrameworkUtil.h"

/**
 * \ingroup V2XFramework
 * \brief Takes decision for a vehicle giving the received messages
 *
 * Takes decisions based on the incoming messages. The 'evaluate' methods,
 * are called when a message should be evaluated (please note that they are empty
 * now and should be implemented)
 */
class FLOURISHV2XFRAMEWORKEXPORT FlourishVehicleRulesEngine: public V2XRulesEngine
{
public:
	/**
	 * \brief Constructor
	 */
	FlourishVehicleRulesEngine();

	/**
	 * \brief Deconstructor
	 */
	virtual ~FlourishVehicleRulesEngine();

	/**
	 * \brief Evaluate a CAM message
	 * \param message Message to evaluate
	 * \param agent Agent who received the message
	 */
	virtual void evaluate( const QSharedPointer<const CAMMessage> &message, V2XSimpleAP *agent) Q_DECL_OVERRIDE;
	/**
	 * \brief Evaluate a DENM message
	 * \param message Message to evaluate
	 * \param agent Agent who received the message
	 */
	virtual void evaluate( const QSharedPointer<const DENMMessage> &message, V2XSimpleAP *agent) Q_DECL_OVERRIDE;
	/**
	 * \brief Evaluate a SPATEM message
	 * \param message Message to evaluate
	 * \param agent Agent who received the message
	 */
	virtual void evaluate( const QSharedPointer<const SPATEMMessage> &message, V2XSimpleAP *agent) Q_DECL_OVERRIDE;
	/**
	 * \brief Evaluate a MAPEM message
	 * \param message Message to evaluate
	 * \param agent Agent who received the message
	 */
	virtual void evaluate( const QSharedPointer<const MAPEMMessage> &message, V2XSimpleAP *agent) Q_DECL_OVERRIDE;
};
