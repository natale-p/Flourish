#include "FlourishCAMMessage.h"

FlourishCAMMessage::FlourishCAMMessage(): V2XMessage()
{
}


FlourishCAMMessage::~FlourishCAMMessage()
{
}

V2XMessage *FlourishCAMMessage::copy() const
{
	FlourishCAMMessage * res = new FlourishCAMMessage();
	res->messageContent = messageContent;
	res->timeStamp = timeStamp;
	return res;
}


CAMMessage &FlourishCAMMessage::getCamMessageContent()
{
	return messageContent;
}

void  FlourishCAMMessage::setTimeStamp(double avalue)
{
	timeStamp = avalue;
}


void FlourishCAMMessage::print() const
{
	qDebug("FlourishCAMMessage : Time Stamp = %f",timeStamp);
	qDebug("FlourishCAMMessage : Message Content");
	messageContent.print();
}
