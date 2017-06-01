/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "V2XMessage.h"
#include "QSharedPointer"

// Later this will be eliminated, and V2XMessage will inherit from Packet
/**
 * \ingroup V2XFramework
 * \brief Represent a Packet
 */
typedef V2XMessage Packet;

/**
 * \brief A shared packet pointer. No need to delete anything.
 */
typedef QSharedPointer<Packet> PacketPointer;
/**
 * \brief A list of shared packet pointers. No need to delete anything.
 */
typedef QList<PacketPointer> PacketPointerList;
