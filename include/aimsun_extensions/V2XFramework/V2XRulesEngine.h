/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once
#include "V2XFrameworkUtil.h"
#include <QSharedPointer>
#include <CAMMessage.h>
#include <DENMMessage.h>
#include <SPATEMMessage.h>
#include <MAPEMMessage.h>

class V2XSimpleAP;

/**
 * \ingroup V2XFramework
 * \brief The VehicleRulesEngine class is responsible to read messages and
 * take decisions based on the content of these messages.
 *
 * This is a pure interface class.
 */
class V2XFRAMEWORKEXPORT V2XRulesEngine
{
	Q_DISABLE_COPY(V2XRulesEngine)
public:
	/**
	 * \brief Constructor
	 */
	V2XRulesEngine();

	/**
	 * \brief Deconstructor
	 */
	virtual ~V2XRulesEngine();

	/**
	 * \brief Evaluate a CAM message
	 * \param message pointer to the CAM message
	 * \param agent the agent originating the request
	 */
	virtual void evaluate( const QSharedPointer<const CAMMessage> &message, V2XSimpleAP *agent) = 0;
	/**
	 * \brief Evaluate a DENM message
	 * \param message pointer to the CAM message
	 * \param agent the agent originating the request
	 */
	virtual void evaluate( const QSharedPointer<const DENMMessage> &message, V2XSimpleAP *agent) = 0;
	/**
	 * \brief Evaluate a SPATEM message
	 * \param message pointer to the CAM message
	 * \param agent the agent originating the request
	 */
	virtual void evaluate( const QSharedPointer<const SPATEMMessage> &message, V2XSimpleAP *agent) = 0;
	/**
	 * \brief Evaluate a MAPEM message
	 * \param message pointer to the MAP message
	 * \param agent the agent originating the request
	 */
	virtual void evaluate( const QSharedPointer<const MAPEMMessage> &message, V2XSimpleAP *agent) = 0;
};
