#pragma once
#include "../DTAUtil.h"

#include <QString>


class GKModel;
class GKExperiment;

class DTAEXPORT ADynamicAPISetup
{
public:
	ADynamicAPISetup(GKModel * handlerMod, GKExperiment *handlerExp);
	virtual ~ADynamicAPISetup();

	/*! It adds a new column (attribute) to GKExperiment.*/
	int addColumn(const QString & iname, const QString & aname );

	/*! It gets a unique id of a column (attribute) from GKExperiment.*/
	int getColumn(const QString & iname) const;

	/*! It retrieves the value of a column (attribute) defined inside the experiment that defines the parameters for the simulation .*/
	double getExperimentValue(int acolumn) const;
	/*! It sets the value of a column (attribute) defined inside the experiment that defines the parameters for the simulation .*/
	void setExperimentValue(int acolumn, double avalue);

private:
	class Private;
	Private *m;

};

