/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include <QSharedDataPointer>
#include "V2XFrameworkUtil.h"
#include "V2XMessage.h"
#include "Asn1cContainer.h"
#include "ITS-spec/MAPEM.h"

/**
 * \ingroup V2XFramework
 * \brief A MAPEM message
 *
 * Represents a MAPEM Message through the use of ASN1CContainer.
 *
 */
class V2XFRAMEWORKEXPORT MAPEMMessage: public V2XMessage
{
public:
	/**
	 * \brief MAPEMMessage constructor
	 */
	MAPEMMessage();
	/**
	 * \brief MAPEMMessage copy constructor
	 * \param other the copy
	 */
	MAPEMMessage(const MAPEMMessage &other);
	/**
	 * \brief Deconstructor
	 */
	virtual ~MAPEMMessage();

	/**
	 * \brief Copy the message content (shallow copy)
	 * \return a copy of the message
	 */
	virtual V2XMessage *copy() const;
	/**
	 * \brief print the message over console in XML format
	 */
	virtual void print() const;

	/**
	 * \brief get the size of a message
	 * \return the size of a message
	 */
	virtual quint32 getSize() const;

	/**
	 * \brief Build this object from an XML representation
	 * \param buf buffer of the representation
	 * \param size size of the buffer
	 * \return true if the construction was fine
	 */
	bool fromXML(const char *buf, size_t size);
	/**
	 * \brief Build this object from a file containing an XML representation
	 * \param filename File name
	 * \return true if the construction was fine
	 */
	bool fromXML(const char *filename);

	/**
	 * \brief Write this message in an XML format
	 * \param out output stream
	 * \return true if everything went fine
	 */
	bool toXML(std::ostream *out) const;

	/**
	 * \brief Print the message to the console
	 */
	void toConsole() const { m_message->toConsole();}

	/**
	 * \brief Read-only data access
	 * \return A copy of the data
	 */
	const MAPEM_t* constData() const;

	/**
	 * \brief data Write data access
	 * \return  A copy of the data
	 */
	MAPEM_t* data();

	/**
	 * \brief Allocate raw data for directly manipulating it
	 */
	void initializeEmpty() { m_message->initializeEmpty(); }

private:
	QSharedDataPointer< ASN1CContainer<MAPEM_t> > m_message; //!< The message
};
