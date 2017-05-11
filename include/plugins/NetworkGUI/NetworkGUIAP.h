/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include "NetworkGUIUtil.h"
#include "GKCircle.h"

//---- NetworkGUIAPInitType ------------------------------------------------------------------------------------------

extern "C" NETWORKGUIEXPORT void NetworkGUIAPInitType( GKModel *model, GKType *type );

//---- NetworkGUIAPFactory -------------------------------------------------------------------------------------------

extern "C" NETWORKGUIEXPORT GKObject * NetworkGUIAPFactory( GKModel *model, GKType *type );

//---- NetworkGUIAP --------------------------------------------------------------------------------------------------

class NETWORKGUIEXPORT NetworkGUIAP : public GKCircle
{
public:
	NetworkGUIAP();
	~NetworkGUIAP();
	void store( GKDataStream &s );
	void restore( GKDataStream &s );

	bool toJson( GKJSonStorer &context, GKJsonObjectParts &parts ) const;
	bool fromJson( GKJSonStorer &context, const GKJsonObjectParts &parts );

	virtual void init() Q_DECL_OVERRIDE;
};
