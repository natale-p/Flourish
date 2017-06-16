/**
  * Copyright TSS 2017
  *
  */
#pragma once
#include "ADynamicAPIUtil.h"
#include <QString>

class GKModel;
class GKExperiment;
class GKBaseObject;
class GKObject;
class GKType;
class GKFolder;
class GKColumn;
class GKPreferencesGroup;
class DTAVehicleType;

/**
 * \ingroup ADynamicAPI
 * \brief The interface between the internals of Aimsun with the outside
 *
 * In this class are reported all the typical functionalities needed by
 * a plugin based on ADynamicAPI.
 * The interface, right now, is mainly towards the type and their attributes.
 * In Aimsun there are types (for example, each vehicle is of type GKVehicle)
 * and each type can have multiple attributes, represented by columns (because
 * in the user interface they are reported as such).
 *
 * To add a custom attribute to a know type, usually the workflow is:
 * \verbatim
if (! setup.addColumnToType (myType, myAttributeName, translatableAttributeName, ADynamicAPISetup::Double))
	qDebug () << "Can't add the type";
else
	// Attribute added successfully
\endverbatim
 *
 * To retrieve a value, it is necessary to understand that an attribute usually
 * changes across different instances of the type. For example, an attribute
 * for a vehicle can have different value, depending on the vehicle (the vehicle
 * A can have the attribute set to 2.0, while the vehicle B can have 4.0).
 *
 * So, the retrieval is usually tied up with an object:
 * \verbatim
...
GKObject *obj = ... // someone passes that pointer to us
qDebug() << "value:" << setup.getTypeValueDoubleFrom(obj, myType, myAttributeName);
\endverbatim
 *
 * There are methods which are meant to be NOT called from outside aimsun. Usually,
 * for these methods you will not have access to the right include file to use
 * the object (for instance, createType, getObjInFolder, findType, findFolder,
 * are not meant to be used from outside, but they can be used from framework
 * which uses ADynamicAPI but are inside Aimsun).
 */
class ADYNAMICAPIEXPORT ADynamicAPISetup
{
public:
	/**
	 * \brief ADynamicAPISetup default constructor
	 *
	 * Aimsun is forced to use this constructor; the other one is used only
	 * to have a empty constructor while waiting for a copy to be made
	 *
	 * \param handlerMod the GKModel
	 * \param handlerExp the GKExperiment
	 */
	ADynamicAPISetup(GKModel * handlerMod, GKExperiment *handlerExp);

	/**
	 * \brief Empty constructor
	 *
	 * The object is in an invalid state.
	 */
	ADynamicAPISetup();

	/**
	 * \brief Copy constructor
	 * \param other Other instance of ADynamicAPISetup
	 */
	ADynamicAPISetup(const ADynamicAPISetup &other);

	/**
	 * \brief Assignment operator
	 * \param b Other instance of ADynamicAPISetup
	 * \return *this
	 */
	ADynamicAPISetup& operator =(const ADynamicAPISetup& b);

	/**
	 * \brief Deconstructor
	 */
	virtual ~ADynamicAPISetup();

	/**
	 * \brief Available attribute types (copy pasted from GKColumn)
	 */
	enum Type { Invalid, Map, List, String, StringList, Font, Pixmap, Brush, Rect, Size, Color, Palette, ColorGroup,
		IconSet, Point, Image, Int, UInt, Bool, Double, CString, PointArray, Region, Bitmap, Cursor, SizePolicy,
		Date, Time, DateTime, ByteArray, _GKObject, _GKSegmentedAttribute_Obsolete, _GKTimeSerie, _GKEnum, _GKTimeDuration,
		_GKObjectList, _GKColumn, _GKType, _GKContent, File, Void, _GKNormalDistributionParameters };

	/** \brief It adds a new column (attribute) to GKExperiment.
	 *
	 * \param internalName Attribute name (internal, should be in the form yy::zz.
	 * It will be prepended by "GKExperiment::" to form a complete name
	 * "GKExperiment::yy::zz").
	 * \param guiName Translatable name for the GUI
	 * \param columnType Type of the column
	 *
	 * \return -1 in case of failure, otherwise the attribute ID
	 */
	int addExperimentColumn(const QString & internalName, const QString & guiName,
							ADynamicAPISetup::Type columnType);

	/** \brief It adds a new column (attribute) to a Type.
	 *
	 * \param typeName The type name
	 * \param internalName Attribute name (internal, should be in the form yy::zz.
	 * It will be prepended by the type name, so if the type is "GKExperiment"
	 * the final name will be "GKExperiment::yy::zz").
	 * \param guiName Translatable name for the GUI
	 * \param columnType The column type
	 *
	 * \return -1 in case of failure, otherwise the attribute ID
	 */
	int addTypeColumn(const QString & typeName, const QString & internalName,
					  const QString & guiName, ADynamicAPISetup::Type columnType) const;

	/**
	 * \brief Gets a unique id of a column (attribute) from GKExperiment.
	 * \param internalName Internal attribute name
	 * \return The unique id of the attribute from GKExperiment
	 */
	int getExperimentColumnId(const QString & internalName) const;

	/**
	 * \brief Gets a unique id of a column (attribute) for a generic type
	 * \param typeName The type name
	 * \param internalName Internal attribute name
	 * \return The unique id of the attribute
	 */
	int getTypeColumnID(const QString &typeName, const QString &internalName) const;

	/**
	 * \brief Get the value of an experiment attribute represented by the column id
	 * \param columnId The column ID
	 *
	 * \return the attribute value (implemented only for double values)
	 */
	template<class T> T getExperimentValue (int columnId) const;

	/**
	 * \brief Get the value of an attribute over an object
	 * \param from The object
	 * \param typeName The typename of the object
	 * \param internalName The internal name of the attribute
	 */
	template<class T> T getObjectValue (const GKBaseObject *from, const QString & typeName,
										const QString & internalName) const;

	/**
	 * \brief Get the value of an attribute over an object
	 * \param from The object
	 * \param typeName The typename of the object
	 * \param internalName The internal name of the attribute
	 */
	template<class T> T getObjectValue (const DTAVehicleType *from, const QString & typeName,
										const QString & internalName) const;

	/**
	 * \brief Get the value of an attribute over an object
	 * \param from The object
	 * \param typeName The typename of the object
	 * \param internalName The internal name of the attribute
	 */
	template<class T> T getObjectValue (const GKObject *from, const QString & typeName,
										const QString & internalName) const;

	/**
	 * \brief Sets the value of a column (attribute) defined inside the experiment
	 * \param acolumn The column ID
	 * \param avalue The value
	 */
	void setExperimentValue(int acolumn, double avalue);

	/**
	 * \brief Define a preference for the attributes.
	 */
	struct UserPreference {
		QString internalName;	//!< \brief Internal name
		QString guiName;		//!< \brief GUI name (translatable) */
		Type type;				//!< \brief Type of the attribute */
		QString defaultValue;	//!< \brief Default value */
	};

	/**
	 * \brief Create a preference group
	 * \param internalName the internal name of the preference
	 * \param guiName the (translatable) name of the preference
	 * \return a (opaque) pointer to the newly created group
	 */
	GKPreferencesGroup* createPreferenceGroup ( const QString & internalName, const QString & guiName);

	/**
	 * \brief Create a preference inside a group
	 * \param group Pointer to the group
	 * \param preferenceDef Structure containing the preference settings
	 */
	void createPreference ( GKPreferencesGroup *group, const UserPreference &preferenceDef ) const;

	/**
	 * \brief Get the preference value for the preference specified
	 * \param internalName Internal name of the preference
	 * \param obj Object on which check the default value
	 * \return the preference selected, or an empty string
	 */
	QString getPreference (const QString& internalName, const GKObject *obj = nullptr) const;

	/**
	 * \brief Get the preference value for the preference specified
	 * \param internalName Internal name of the preference
	 * \param obj Object on which check the default value
	 * \return the preference selected, or an empty string
	 */
	QString getPreference ( const QString& internalName, const GKBaseObject *obj = nullptr) const;

	/**
	 * \brief Get the preference value for the preference specified
	 * \param internalName Internal name of the preference
	 * \param obj Object on which check the default value
	 * \return the preference selected, or an empty string
	 */
	QString getPreference ( const QString& internalName, const DTAVehicleType *obj = nullptr) const;

	//
	// NOT USABLE FROM OUTSIDE AIMSUN
	//
	/**
	 * \brief Create a custom type inside Aimsun
	 * \param typeName Name of the type
	 * \param superType Parent type
	 * \param guiName Translatable name for the GUI
	 * \return A pointer to the newly created type
	 */
	GKType* createType (const QString & typeName, const QString &superType,
						const QString & guiName);

	/*!
	 * \brief Get a list of objects in a specific folder
	 *
	 * \return a list of object
	 */
	QList<GKObject*> getObjInFolder(const GKFolder *folder) const;

	/**
	 * \brief Find a type giving the name
	 * \param typeName The typename
	 * \return A pointer to the type if it exists, nullptr otherwise
	 */
	GKType* findType (const QString &typeName) const;

	/**
	 * \brief Find a folder giving its name
	 * \param layerFolder The folder name
	 * \return The folder pointer
	 */
	GKFolder* findFolder(const QString &layerFolder) const;

	/**
	 * \brief Get a column from a type
	 *
	 * \param typeName Name of the type
	 * \param internalName Name of the column
	 * \return a pointer to GKColumn if found, nullptr otherwise
	 */
	GKColumn* getTypeColumn(const QString &typeName, const QString &internalName) const;

	/**
	 * \brief Get a pointer to the current experiment
	 *
	 * \return an (opaque) pointer to the experiment
	 */
	const GKExperiment *getExperiment () const;

private:
	/**
	 * \brief Private impl class
	 */
	class Private;
	Private *m; /**!< Private impl pointer */
};

