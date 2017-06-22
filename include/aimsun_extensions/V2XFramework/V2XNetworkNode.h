/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once
#include <QtCore>
//#include "Aggregate.h"
#include "V2XFrameworkUtil.h"

class NetDevice;
class GKPoint;

class V2XFRAMEWORKEXPORT V2XNetworkPoint
{
public:
	V2XNetworkPoint();
	V2XNetworkPoint(const GKPoint *point);
	V2XNetworkPoint(double x, double y, double z);
	~V2XNetworkPoint();

	//! Distance between "this" point and point "c" whitout use Z coordinate.
	double distance2D( const V2XNetworkPoint & c ) const;
	//! Distance between "this" point and point "c".
	double distance3D( const V2XNetworkPoint & c ) const;

	double		x;	//!< X coordinate of the point
	double		y;	//!< Y coordinate of the point
	double		z;	//!< Z coordinate of the point


	bool operator == ( const V2XNetworkPoint & c ) const;
	/*! Operator that returns true if the two compared points are different.
		This operator returns false if the points are equal.
	*/
	bool operator != ( const V2XNetworkPoint & c ) const;

	/*! Operator that adds one point to another.*/
	V2XNetworkPoint & operator += ( const V2XNetworkPoint & c );
	/*! Operator that subtracts one point to another.*/
	V2XNetworkPoint & operator -= ( const V2XNetworkPoint & c );

	V2XNetworkPoint &operator *=(double f);

	/*! Operator that adds one point to another.*/
	V2XNetworkPoint operator + ( const V2XNetworkPoint & c ) const;
	/*! Operator that subtracts one point to another.*/
	V2XNetworkPoint operator - ( const V2XNetworkPoint & c ) const;
	/*! Operator that adds a scalar to all point components*/
	V2XNetworkPoint operator + (double c) const = delete;
	/*! Operator that subtracts a scalar to all point components.*/
	V2XNetworkPoint operator - (double c) const = delete;
	/*! Operator that multiplies a scalar to all point components*/
	V2XNetworkPoint operator * (double c) const = delete;
	/*! Operator that divides a scalar to all point components*/
	V2XNetworkPoint operator / (double c) const = delete;

	//! Dot product
	double operator*(const V2XNetworkPoint &c) const;

};

/**
 * \ingroup V2XFramework
 * \brief Represents a time with respect to some initial reference point
 *
 * The reference point could be the simulation start, or another fixed point
 * in time. Please refer to the documentation of the variable to know what is
 * the reference time.
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
 * It represents any object with a connection. It has two different time values:
 * the first is the so-called absolute time, and represents the time since the
 * beginning of the simulation. The second one, called time of the day, it is the
 * difference between now and midnight (00:00.00) of the current day.
 *
 * A network node has also a position; moreover, different objects have
 * different id. The ID should be unique, or otherwise a lot of problems
 * will appear.
 *
 * To retrieve the values, use the associated getters.
 *
 * \see getId
 * \see getTimeOfTheDay
 * \see getAbsTime
 * \see getPosition
 */
class V2XFRAMEWORKEXPORT V2XNetworkNode : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(V2XNetworkNode)
public:
	/**
	 * \brief Constructor with an id
	 *
	 * \param id Given ID
	 */
	V2XNetworkNode(quint32 id);

	/**
	 * \brief Deconstructor
	 */
	virtual ~V2XNetworkNode ();

	/**
	 * \brief operator ==
	 * \param other other node
	 * \return true if the ID are the same (assumption: ID are unique)
	 */
	bool operator == (const V2XNetworkNode &other) const {
		return (getId() == other.getId());
	}
	/**
	 * \brief Get the ID of the node
	 * \return the ID of the node
	 */
	quint64 getId () const { return m_id; }
	/**
	 * \brief Get the position of the node
	 * \return the position of the node
	 */
	virtual V2XNetworkPoint getPosition () const = 0;

	/**
	 * \brief Update the time of the day in this node
	 *
	 * \param time the current time
	 */
	void setTimeOfTheDay(const V2XNetworkTime &time) { m_timeOfTheDay = time; }

	/**
	 * \brief Get the current time for the node
	 * \return The current time
	 */
	V2XNetworkTime getTimeOfTheDay () const { return m_timeOfTheDay; }

	/**
	 * \brief Update the absolute time in this node
	 * \param time the current absolute time
	 */
	void setAbsTime (const V2XNetworkTime &time) { m_absTime = time; }

	/**
	 * \brief Get the current absolute time for the node
	 * \return The current absolute time
	 */
	V2XNetworkTime getAbsTime() const { return m_absTime; }

protected:
	QPointer<NetDevice> m_dev;		//!< Device
	V2XNetworkTime m_timeOfTheDay;	//!< Time of the day
	V2XNetworkTime m_absTime;		//!< Absolute time

private:
	quint32 m_id;					//!< ID
};
