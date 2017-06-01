//-*-Mode: C++;-*-
#ifndef _GKGeoUtil_h_
#define _GKGeoUtil_h_
//SDK	

#include "GKUtil.h"

class GKPoint;

typedef double GKCoord;
double GKEXPORT GKLerp( double a, double b, double f );
int GKEXPORT vectSign(const GKPoint & p1, const GKPoint & p2, const GKPoint & p3, const GKPoint & p4);

#endif
