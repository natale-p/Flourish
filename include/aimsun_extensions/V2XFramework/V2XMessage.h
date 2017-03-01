#pragma once

#include "V2XFrameworkUtil.h"

class V2XFRAMEWORKEXPORT V2XMessage
{
public:

	V2XMessage();
	virtual ~V2XMessage();

	enum TypeMess {eNA = 0, eCAM = 1 };

	virtual V2XMessage *copy() const = 0;
	virtual void print() const = 0;
};

