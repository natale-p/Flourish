#include "FlourishV2XBroker.h"
#include "FlourishCAMMessage.h"

FlourishV2XBroker::FlourishV2XBroker(): V2XRandomBroker()
{

}

FlourishV2XBroker::~FlourishV2XBroker()
{

}

V2XMessage *FlourishV2XBroker::getNewMessage(int atype)
{
	V2XMessage *res = nullptr;
	if (atype == V2XMessage::TypeMess::eCAM){
		res = new FlourishCAMMessage();
	}
	return res;
}


