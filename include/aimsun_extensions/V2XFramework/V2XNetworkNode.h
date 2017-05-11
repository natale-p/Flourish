/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once
#include <QtCore>
//#include "Aggregate.h"
#include "GKPoint.h"
#include "V2XFrameworkUtil.h"

class NetDevice;

/**
 * \ingroup V2XFramework
 * \brief Represents a time with respect to the simulation start
 *
 * The implementation is expected to change to use big integer representing
 * milliseconds.
 *
 */
class V2XFRAMEWORKEXPORT V2XNetworkTime
{
public:
	/**
	 * \brief Create an unusable time object
	 * \see fromSeconds
	 */
	V2XNetworkTime () { m_time = -1.0; }

	/**
	 * \brief Copy constructor
	 * \param other other time
	 */
	V2XNetworkTime (const V2XNetworkTime &other) { m_time = other.m_time; }

	/**
	 * \brief operator ==
	 * \param other other V2XNetworkTime
	 * \return true if the times are the same
	 */
	bool operator == (const V2XNetworkTime &other) const {
		// TODO: Insert a comparison with an epsilon ... or KILL DOUBLE
		return (this->getSeconds() == other.getSeconds ());
	}
	/**
	 * \brief Initialize the object to a value represented in seconds
	 * \param time Time value
	 */
	void fromSeconds (double time) { m_time = time; }
	/**
	 * \brief Get the value of the object in seconds
	 * \return seconds
	 */
	double getSeconds () const { Q_ASSERT (m_time >= 0.0); return m_time; }
	/**
	 * \brief Get the value of the object in milliseconds
	 *
	 * \return milliseconds
	 */
	double getMilliseconds () const { Q_ASSERT (m_time >= 0.0); return 1000*m_time; }

private:
	double m_time; /**!< The data */
};

/**
 * \ingroup V2XFramework
 * \brief A Node in the network
 *
 * It represents any object with a connection. It has an internal time, and
 * a position. Different objects have different id; it is guaranteed to have
 * an unique value (except for quint32 wrap-around).
 *
 * To retrieve the values, use the associated getters.
 *
 * \see getId
 * \see getCurrentTime
 * \see getPosition
 */
class V2XFRAMEWORKEXPORT V2XNetworkNode : public QObject
{
	Q_OBJECT
public:
	/**
	 * \brief Constructor
	 */
	V2XNetworkNode();
	/**
	 * \brief Deconstructor
	 */
	virtual ~V2XNetworkNode () { }

	/**
	 * \brief operator ==
	 * \param other other node
	 * \return true if the ID are the same (assumption: ID are unique)
	 */
	bool operator == (const V2XNetworkNode &other) const {
		return (getId() == other.getId());
	}
	/**
	 * \brief Get the current time for the node
	 * \return The current time
	 */
	V2XNetworkTime getCurrentTime () const { return m_currentTime; }
	/**
	 * \brief Get the ID of the node
	 * \return the ID of the node
	 */
	quint64 getId () const { return m_id; }
	/**
	 * \brief Get the position of the node
	 * \return the position of the node
	 */
	GKPoint getPosition () const { return m_position; }

	/**
	 * \brief Update the time in this node
	 *
	 * \param time the current time
	 */
	void setTime(const V2XNetworkTime &time) { m_currentTime = time; }

protected:
	GKPoint m_position; /**!< The position */
	QPointer<NetDevice> m_dev; /**!< Device*/
	V2XNetworkTime m_currentTime; /**!< The current time */

private:
	quint64 m_id; /**!< ID */
};
