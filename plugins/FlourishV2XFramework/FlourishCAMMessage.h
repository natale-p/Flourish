//-*-Mode: C++;-*-
#pragma once

#include "V2XMessage.h"
#include "CAMMessage.h"
#include <QString>


class FlourishConnectedAgent;


class FlourishCAMMessage: public V2XMessage
{
public:
	FlourishCAMMessage();
	virtual ~FlourishCAMMessage();

	virtual V2XMessage *copy() const;

	CAMMessage &getCamMessageContent();
	void  setTimeStamp(double avalue);

	virtual void print() const;


private:
	CAMMessage messageContent;
	double timeStamp;
};
