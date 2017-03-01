#include "FlourishConnectedAgent.h"

#include "FlourishV2XBroker.h"
#include "FlourishCAMMessage.h"
#include "FlourishVehicleRulesEngine.h"

#ifdef _WIN32

	#pragma warning(disable: 4251)
	#pragma warning(disable: 4786)
	#pragma warning(disable: 4503)
//	#pragma warning(disable: 4284)
#endif



FlourishConnectedAgent::FlourishConnectedAgent(unsigned short idhandler, void *agent, VehicleRulesEngine * const avehRules, V2XBroker * const abroker): ConnectedAgent(idhandler, agent, avehRules, abroker)
{
	V2XBroker * abrokerC = getBroker();
	if (abrokerC != nullptr){
		abrokerC->vehSubscription(this);
	}
}

FlourishConnectedAgent::~FlourishConnectedAgent()
{
	V2XBroker * abroker = getBroker();
	if (abroker != nullptr){
		abroker->vehUnsubscription(this);
	}
}

void FlourishConnectedAgent::buildCAMMessage(double time, double timeSta, FlourishCAMMessage & mess)
{

	mess.setTimeStamp(time);
	CAMMessage & camMessageContent = mess.getCamMessageContent();
	ItsPduHeader & header = camMessageContent.getItsPduHeader();

	header.setProtocolVersion(1);
	header.setMessageId(ItsPduHeader::eCam);
	header.setStationId(getId());

	CoopAwareness & cam = camMessageContent.getCoopAwareness();
	cam.setGenerationDeltaTime(time);

	CamParameters &camParam = cam.getCamParameters();


	BasicContainer & basicContainer = camParam.getBasicContainer();
	// check different vehTypes: how they are defined
	basicContainer.setStationType(BasicContainer::ePassengerCar);
	ReferencePosition refFront, refBack;
	getCoordinates(refFront.x, refFront.y, refFront.z, refBack.x, refBack.y , refBack.z);
	basicContainer.setReferencePosition( refFront);


	HighFrequencyContainer &highFrequencyContainer = camParam.getHighFrequencyContainer();
	BasicVehicleContainerHighFrequency &basicVehicleContainerHighFrequency = highFrequencyContainer.getBasicVehicleContainerHighFrequency();
	basicVehicleContainerHighFrequency.setHeading(BasicVehicleContainerHighFrequency::eNAHead);
	basicVehicleContainerHighFrequency.setSpeed(getSpeed());
	basicVehicleContainerHighFrequency.setDriveDirection(BasicVehicleContainerHighFrequency::eForward);
	basicVehicleContainerHighFrequency.setVehicleLength(getLength());
	basicVehicleContainerHighFrequency.setVehicleWidth(getWidth());
	basicVehicleContainerHighFrequency.setLongitudinalAcceleration(getAcceleration());
	basicVehicleContainerHighFrequency.setCurvature(0);
	basicVehicleContainerHighFrequency.setCurvatureCalculationMode(BasicVehicleContainerHighFrequency::eNACurvC);

}

void FlourishConnectedAgent::getState(double time, double timeSta)
{
	FlourishCAMMessage * message = dynamic_cast <FlourishCAMMessage *> (v2xbrokerItem->getNewMessage(V2XMessage::TypeMess::eCAM));
	if (message != nullptr){
		buildCAMMessage(time, timeSta, *message);
		V2XBroker * abroker = getBroker();
		if (abroker != nullptr){
			abroker->broadcast(time, message);
		}
	}
}



void FlourishConnectedAgent::setState(double time, double timeSta)
{
	if (getVehicleRulesEngine() != nullptr){
		getVehicleRulesEngine()->evaluate(this);
	}
	qDeleteAll(bufferMessages);
	bufferMessages.clear();
}
