/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "FlourishV2XFrameworkUtil.h"
#include "V2XSimpleAP.h"
#include "FlourishInfrastructureRulesEngine.h"
#include "ADynamicAPISetup.h"

/**
 * \ingroup FlourishV2X
 * \brief A non-mobile infrastructure
 *
 * When it receives a message, the method received is invoked.
 * To generate a message, use the method generateMessage.
 */
class FLOURISHV2XFRAMEWORKEXPORT FlourishAP: public V2XSimpleAP
{
public:
	/**
	 * \brief Constructor for an AP
	 * \param id Unique ID for the object
	 * \param obj An object in aimsun representing this AP
	 * \param setup The Setup API
	 */
	FlourishAP(quint32 id, const GKObject *obj, const ADynamicAPISetup &setup);

public slots:
	/**
	 * \brief A message has been received
	 * \param device Device which has received the message
	 * \param packet Packet received
	 * \param addr Source address
	 */
	virtual void received (const QPointer<NetDevice> &device,
						   const QSharedPointer<const Packet> &packet, const Address &addr) Q_DECL_OVERRIDE;
protected:
	/**
	 * \brief Generate messages to be transmitted
	 *
	 * \return A list of messages
	 */
	virtual PacketPointerList generateMessage() Q_DECL_OVERRIDE;

	/**
	 * \brief Generate a DENM message
	 * \return A DENM message
	 */
	PacketPointer generateDENM();

	/**
	 * \brief Generate a SPATEM message
	 *
	 * The SPATEM in the current implementation refers to a single intersection.
	 *
	 * \param intersection Intersection pointer
	 * \return A SPATEM message
	 */
	PacketPointer generateSPATEM( const V2XIntersectionPointer &intersection);

	/**
	 * \brief Generate a MAPEM message
	 *
	 * The MAPEM in the current implementation refers to a single intersection.
	 *
	 * \param intersection Intersection pointer
	 * \return
	 */
	PacketPointer generateMAPEM( const V2XIntersectionPointer &intersection );
private:
	FlourishInfrastructureRulesEngine m_engine; /**!< Engine instance */
	ADynamicAPISetup m_setup;
};
