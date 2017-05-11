#pragma once
#include "../DTAUtil.h"

#include <QString>


class GKModel;
class GKExperiment;
class GKObject;
class GKType;
class GKLayer;
class GKFolder;
class GKColumn;

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

	/*!
	 * \brief Get a list of access point set through the GUI
	 *
	 * \return a list of object, to be casted to NetworkGUIAP
	 */
	QList<GKObject*> getObjInFolder(const GKFolder *folder) const;

	GKType* createType (const QString & typeName, const QString &superType,
						const QString & guiName);

	GKType* findType (const QString &typeName) const;

	GKFolder* findFolder(const QString &layerFolder) const;

private:
	class Private;
	Private *m;
};

