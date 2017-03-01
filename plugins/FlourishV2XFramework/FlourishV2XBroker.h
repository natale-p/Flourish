//-*-Mode: C++;-*-
#pragma once

#include "V2XRandomBroker.h"


class V2XMessage;
class ConnectedAgent;

class FlourishV2XBroker: public V2XRandomBroker
{
public:
	FlourishV2XBroker();
	virtual ~FlourishV2XBroker();


	virtual V2XMessage *getNewMessage(int atype);

private:



};
