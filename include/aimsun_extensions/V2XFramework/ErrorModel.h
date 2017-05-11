/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "Packet.h"
#include <QtCore>
#include <FRand.h>
#include "V2XFrameworkUtil.h"

/**
 * \ingroup V2XFramework
 * \brief A general (but empty) error model
 */
class V2XFRAMEWORKEXPORT ErrorModel : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(ErrorModel)
public:
	ErrorModel ();
	virtual ~ErrorModel ();

	/**
	 * Note:  Depending on the error model, this function may or may not
	 * alter the contents of the packet upon returning true.
	 *
	 * \returns true if the Packet is to be considered as errored/corrupted
	 * \param pkt Packet to apply error model to
	 */
	bool isCorrupt (QSharedPointer<Packet> pkt);
	/**
	 * Reset any state associated with the error model
	 */
	void reset (void);
	/**
	 * Enable the error model
	 */
	void enable (void);
	/**
	 * Disable the error model
	 */
	void disable (void);
	/**
	 * \return true if error model is enabled; false otherwise
	 */
	bool isEnabled (void) const;

private:
	/**
	 * Corrupt a packet according to the specified model.
	 * \param p the packet to corrupt
	 * \returns true if the packet is corrupted
	 */
	virtual bool doCorrupt (QSharedPointer<Packet> p) = 0;
	/**
	 * Re-initialize any state
	 */
	virtual void doReset (void) = 0;

	bool m_enable; //!< True if the error model is enabled
};

/**
 * \brief Determine which packets are errored corresponding to an underlying
 * distribution, rate, and unit.
 *
 * This object is used to flag packets as being lost/errored or not.
 * The two parameters that govern the behavior are the rate (or
 * equivalently, the mean duration/spacing between errors), and the
 * unit (which may be per-bit, per-byte, and per-packet).
 * Users can optionally provide a RandomVariableStream object; the default
 * is to use a Uniform(0,1) distribution.
 * Reset() on this model will do nothing
 *
 * IsCorrupt() will not modify the packet data buffer
 */
class V2XFRAMEWORKEXPORT RateErrorModel : public ErrorModel
{
	Q_OBJECT
	Q_DISABLE_COPY(RateErrorModel)
public:
	RateErrorModel ();
	virtual ~RateErrorModel ();

	/**
	 * Error unit. The error model can be packet, Byte or bit based.
	 */
	enum ErrorUnit
	{
		ERROR_UNIT_BIT,
		ERROR_UNIT_BYTE,
		ERROR_UNIT_PACKET
	};

	/**
	 * \returns the ErrorUnit being used by the underlying model
	 */
	RateErrorModel::ErrorUnit getUnit (void) const;
	/**
	 * \param error_unit the ErrorUnit to be used by the underlying model
	 */
	void setUnit (enum ErrorUnit error_unit);

	/**
	 * \returns the error rate being applied by the model
	 */
	double getRate (void) const;
	/**
	 * \param rate the error rate to be used by the model
	 */
	void setRate (double rate);

	/**
	 * \param seed The seed
	 */
	void setRandomSeed (int seed);

private:
	// inherit
	virtual void doReset (void) Q_DECL_OVERRIDE;
	virtual bool doCorrupt (QSharedPointer<Packet> p) Q_DECL_OVERRIDE;
	/**
	 * Corrupt a packet (packet unit).
	 * \param p the packet to corrupt
	 * \returns true if the packet is corrupted
	 */
	virtual bool doCorruptPkt (QSharedPointer<Packet> p);
	/**
	 * Corrupt a packet (Byte unit).
	 * \param p the packet to corrupt
	 * \returns true if the packet is corrupted
	 */
	virtual bool doCorruptByte (QSharedPointer<Packet> p);
	/**
	 * Corrupt a packet (bit unit).
	 * \param p the packet to corrupt
	 * \returns true if the packet is corrupted
	 */
	virtual bool doCorruptBit (QSharedPointer<Packet> p);

	enum ErrorUnit m_unit; //!< Error rate unit
	double m_rate; //!< Error rate

	ARandomGenerator m_randomGenerator; //!< Random generator
};
