//-*-Mode: C++;-*-
#ifndef _DTAUtil_h_
#define _DTAUtil_h_
//SDK

#include <float.h>
#include <math.h>

#include <qglobal.h>

typedef double DTATime;
typedef std::tuple<int, int, int, int> DTAODKeyType; // slice, vehtype, dest_connection, dest_origin
enum class DTAODKeyTypeIndex : char {Slice=0, Veh=1, DestConnector=2, OriginConnector=3};
const DTATime DTATimeMAX = DBL_MAX;
const DTATime SECONDSDAY = 86400;

enum DTAHeadwayType {eExponential, eQuasiUniform, eNormal, eConstant, eExternal, eASAP, eUnknownArrival};
enum DTARouteType {eRouteChoice, eODRoutes, ePathAssignmentResults, eIterative, ePointToPoint};

inline float DTARound(float num, int precision=2)
{
    return floorf(num * pow(10.0f,precision) + .5f)/pow(10.0f,precision);
}


namespace dta {
	typedef  float percentage;

	inline bool AreEqual( DTATime a, DTATime b, DTATime epsilon = 0.000001 )
	{
		bool res = false;

		if ( (a+epsilon) > b && (a-epsilon) < b ) {
			res = true;
		}
		return res;
	}
	inline int PositiveModulo(int i, int n) {
		return (n + (i % n)) % n;
	}

	inline int AdjustTrips(float value, double value01/*, FILE * f=NULL*/)
	{
		int res = (int)value;
		if ( value > 0 ) {
			float probability = value - floorf(value);
			if (probability>0.0){
				if (value01 <=  probability){
					res++;
				}
			}
		}
		/*if ( f ) {
			fprintf(f, "%f,%f,%f,%d,%d\n", value01, value, value - floorf(value), (int)value, res);
		}*/
		return res;
	}

	template <typename T> T * Realloc( T*& src, int oldSize, int newSize ) {
		T *dst = new T[newSize];
		if ( newSize < oldSize ) {
			// The block is getting smaller
			// Truncate anything past the new end
			oldSize = newSize;
		}
		while ( --oldSize >= 0 ) {
			dst[oldSize] = src[oldSize];
		}
		// Free the old block and reuse the pointer
		delete[] src;
		src = dst;
		// Return the pointer for convenience
		return src;
	}

	template <typename T>
	bool ObjectLessThan(const T *o1, const T *o2)
	{
		quint32 id1 = o1? o1->getId() : 0;
		quint32 id2 = o2? o2->getId() : 0;
		return (id1 < id2);
	}
	//#ifdef _PMESO
	struct Point2D{
		Point2D(){
			x=0.0;
			y=0.0;
    }

    double distance(const Point2D & other) const {
        double dx = this->x-other.x;
        double dy = this->y-other.y;
        return sqrt(dx*dx+dy*dy);
		}
		double x;
		double y;
	};
	//#endif

	template <typename T>
	void pointerSwap(T ** a, T ** b){
		T * aux;
		aux = (*a);
		(*a) = (*b);
		(*b) = aux;
	}

}





#if defined(Q_OS_WIN)
	#ifdef _DTA_DEF
		#define DTAEXPORT __declspec(dllexport)
	#else
		#define DTAEXPORT __declspec(dllimport)
	#endif

	#pragma warning(disable: 4251)
	#pragma warning(disable: 4786)
//	#pragma warning(disable: 4284)
#else
	#if defined(Q_OS_LINUX)
		// it is assumed that in linux we are using gcc >= 4.0
		#define DTAEXPORT __attribute__ ((visibility("default")))
	#else
		#define DTAEXPORT 
	#endif
#endif




#endif
