/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "V2XFrameworkUtil.h"
#include <QtGlobal>

/**
 * \ingroup V2XFramework
 * \brief A message in the V2XFramework
 *
 * The message is, for now, very simple, and does not include
 * serialization/deserialization, as well as any way to encapsulate one
 * in another.
 */
class V2XFRAMEWORKEXPORT V2XMessage
{
public:
	/**
	 * \brief Empty default Constructor
	 */
	V2XMessage() { }

	/**
	 * \brief Empty default deconstructor
	 */
	virtual ~V2XMessage() { }

	/**
	 * \brief Copy the message
	 * \return A copy of the message
	 */
	virtual V2XMessage *copy() const = 0;
	/**
	 * \brief Print the message content (DEPRECATED)
	 */
	virtual void print() const = 0;

	/**
	 * \brief Get the message size
	 * \return the message size
	 */
	virtual quint32 getSize() const = 0;
};

