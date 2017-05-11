/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include <QObject>
#include "V2XFrameworkUtil.h"

class NetDevice;

/**
 * \ingroup V2XFramework
 * \brief Abstract Channel Base Class.
 *
 * \see SimpleChannel
 *
 */
class V2XFRAMEWORKEXPORT Channel : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(Channel)
public:
	/**
	 * \brief Channel constructor
	 */
	Channel() : QObject () { static qint32 id = 0; m_id = id; ++id; }
	/**
	  * \brief Channel deconstructor
	  */
	virtual ~Channel() { }

	/**
	 * \returns the unique id of this channel
	 *
	 * This unique id happens to be also the index of the Channel into
	 * the ChannelList.
	 */
	qint32 getId (void) const { return m_id; }

	/**
	* \returns the number of NetDevices connected to this Channel.
	*/
	virtual quint32 getNDevices (void) const = 0;

private:
	qint32 m_id; //!< Channel id for this channel
};
