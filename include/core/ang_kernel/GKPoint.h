//-*-Mode: C++;-*-
#ifndef _GKPoint_h_
#define _GKPoint_h_
//SDK	

#include "GKGeoUtil.h"
#include <QString>

class GKVector;
class GKTextStream;
class GKLine;

class QDomNode;
//#ifdef _USE_QJSON
//	//#include "QJsonArray"
//	#include <QJsonArray>

//#endif


//---- GKPoint -----------------------------------------------------------
/*! \brief A 3D Point usually in m (or feet). */
/*!
	This 3d point can contain the (x, y, z) coordinates of a point.
	It can be used to contain a 2d point as most of the methods have a default z value asigned to 0.
*/
class GKEXPORT GKPoint
{
public:
	GKPoint();
	GKPoint(GKCoord ax, GKCoord ay, GKCoord az = 0.0f );
	virtual ~GKPoint();

	//! Stores the object in a file
	virtual void storeXML( GKTextStream & s, const QString & name = QString::null );
	//! Restores the object from a file
	virtual void restoreXML( GKTextStream & s, QDomNode & node );

	//! Are points near? epsilon in m...
	bool areEqual ( const GKPoint & c, double epsilon ) const;
	//! Are points near? epsilon in m... It does not take the z coordinate into account
	bool areEqual2D ( const GKPoint & c, double epsilon ) const;

	/*! Operator that returns true if the two compared points are equal.
		This operator returns false if the points are different.
	*/
    bool operator == ( const GKPoint & c ) const;
	/*! Operator that returns true if the two compared points are different.
		This operator returns false if the points are equal.
	*/
    bool operator != ( const GKPoint & c ) const;

	/*! Operator that adds one point to another.*/
    GKPoint & operator += ( const GKPoint & c );
    /*! Operator that subtracts one point to another.*/
    GKPoint & operator -= ( const GKPoint & c );

	GKPoint &operator *=(GKCoord f);

	/*! Operator that adds one point to another.*/
    GKPoint operator + ( const GKPoint & c ) const;
    /*! Operator that subtracts one point to another.*/
    GKPoint operator - ( const GKPoint & c ) const;

	/*! Operator that adds one vector to a point.*/
    GKPoint operator + ( const GKVector & c ) const;
    /*! Operator that subtracts one vector to a point.*/
    GKPoint operator - ( const GKVector & c ) const;

	/*! Operator that adds a scalar to all point components*/
	GKPoint operator + (GKCoord c) const;
	/*! Operator that subtracts a scalar to all point components.*/
	GKPoint operator - (GKCoord c) const;
	/*! Operator that multiplies a scalar to all point components*/
	GKPoint operator * (GKCoord c) const;
	/*! Operator that divides a scalar to all point components*/
	GKPoint operator / (GKCoord c) const;

	/*! Returns true if "this" is diffent of "c" after multiply the coordinates
		by factor and compared each one as intergers
	*/
	bool almostDifferents( const GKPoint & c, GKCoord factor ) const;

	//! Distance between "this" point and point "c" whitout use Z coordinate.
	double distance2D( const GKPoint & c ) const;
	//! Distance between "this" point and point "c".
	double distance3D( const GKPoint & c ) const;

	////////////////////
	// Vector operations
	////////////////////
	//! Length
	double length() const;
	//! Unit vector pointing in the same direction
	GKPoint normalized() const;
	//! Dot product
	GKCoord operator*(const GKPoint &c) const;
	//! Negative operator
	GKPoint operator-() const;
	//! NaN detector
	bool isNaN() const
	{ return (x!=x) || (y!=y) || (z!=z); }


	/*! Sets the (x, y, z) coordinates of the point. */
	void set( GKCoord ax, GKCoord ay, GKCoord az = 0.0f );

//NSDK
	bool alineados( const GKPoint & v2, const GKPoint & v3 ) const;
//NSDK

	/*! Returns the angle that the segment defined by this point and "point" makes with the 
		horitzontal. Between GKPI and -GKPI */
	GKCoord getAngleHorizontalInDegs( const GKPoint & p2 ) const;
	/*! Returns the angle that the segment defined by this point and "point" makes with the 
		horitzontal. Between GKPI and -GKPI */
	GKCoord getAngleHorizontalInRads( const GKPoint & p2 ) const;

	/*! Returns the angle that the line defined by this point and "point" makes with the 
		horitzontal. Between GKPI/2 and -GKPI/2 */
	double getMinAngleHorizontalInRads( const GKPoint & point ) const;
	/*! Returns the angle that the line defined by this point and "point" makes with the 
		vertical. Between GKPI/2 and -GKPI/2 */
	double getMinAngleVerticalInRads( const GKPoint & point ) const;

//NSDK
    friend GKEXPORT QDataStream &operator<<( QDataStream &, const GKPoint & );
    friend GKEXPORT QDataStream &operator>>( QDataStream &, GKPoint & );
//NSDK

	/*! Given a second point, returns the Line in 2 dimensions that goes by them. If the line is
		vertical, it is codified with slope = DBL_MA and coef = x constant */
	GKLine line2DPtp( const GKPoint & p2 ) const;

	/*! Rotates this point, given a center and an angle in radians. The rotated point is returned and this one
		is not modified */
	GKPoint rotate2D( const GKPoint & center, double angle ) const;

	/*! Rotates this point, given a center and an angle in radians, modifying it. */
	void rotate2DThis( const GKPoint & center, double angle );

	//! Lerp: returns (1-f)this + pf
	GKPoint lerp( const GKPoint & p, double f ) const;

	/*! Finds a point p in the line defined by this and p2, at distance "distance" from this 
		going to p2 */
	GKPoint lDist( const GKPoint & p2, double distance ) const;

	/*! Supposing that all three points pertain to the same line, returns true if this
	 is located between p1 and p2; false otherwise. The epsilon is the distance in m 
	 allowed for distorsion */
	bool betweenPoints( const GKPoint & p1, const GKPoint & p2, double epsilon ) const;
	
	/*! Fills the point 'res' that is on the line that goes to point 'p' at distance 'd' 
		If the value returnen is 'false' then an error occourred and 'res' is not filled */
    bool pointAtDistance( const GKPoint& p, const double d, GKPoint & res ) const;

	GKCoord		x;	//!< X coordinate of the point
	GKCoord		y;	//!< Y coordinate of the point
	GKCoord		z;	//!< Z coordinate of the point

	static GKPoint zero;	//!< Point at (0, 0, 0)
	static GKPoint null;	//!< Point at (Nan, Nan, Nan)

	/*! A point is created from a string having the format x,y,z 
		x, y and z coordinates can have different sizes
	*/
	static GKPoint fromString( const QString& str );
	
	/*! Returns a QString having the format x,y,z
	*/
	QString toString() const;

//#ifdef _USE_QJSON
//	QJsonArray toJsonArray() const;
//	void fromJsonArray( const QJsonArray& point);
//#endif
};

Q_DECLARE_TYPEINFO(GKPoint, Q_MOVABLE_TYPE);

/*! Operator that multiplies a scalar to all point components*/
GKEXPORT GKPoint operator*(GKCoord c, GKPoint const &);

//NSDK
GKEXPORT QDataStream &operator>>( QDataStream &, GKPoint & );
GKEXPORT QDataStream &operator<<( QDataStream &, GKPoint const & );
GKEXPORT QDataStream &operator<<( QDataStream &, GKPoint  & );
GKEXPORT QDebug operator<<(QDebug debug, const GKPoint &p);
//NSDK

#endif
