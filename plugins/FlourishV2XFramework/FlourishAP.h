/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */

#include "V2XSimpleAP.h"

class FlourishAP: public V2XSimpleAP
{
public:
	/**
	 * \brief Constructor for an AP
	 * \param position Position of the AP
	 */
	FlourishAP(const GKPoint &position);

public slots:
	/**
	 * \brief A message has been received
	 * \param device Device which has received the message
	 * \param packet Packet received
	 * \param addr Source address
	 */
	virtual void received (const QPointer<NetDevice> &device,
						   const QSharedPointer<const Packet> &packet, const Address &addr);
protected:
	/**
	 * \brief Generate a single message to be transmitted
	 *
	 * \return A packet containing the message
	 */
	virtual QSharedPointer<Packet> generateMessage();
};
