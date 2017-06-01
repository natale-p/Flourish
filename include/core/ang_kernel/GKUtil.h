//-*-Mode: C++;-*-
#ifndef _GKUtil_h_
#define _GKUtil_h_
//SDK

#include <qglobal.h>
#include <qpair.h>
#include <stdio.h>
#include <stdlib.h>



#ifdef _WIN32
	#ifdef _GKDLL_DEF
		#define GKEXPORT __declspec(dllexport)		
	#else
		#define GKEXPORT __declspec(dllimport)
	#endif

	#pragma warning(disable: 4251)
	#pragma warning(disable: 4786)
	#pragma warning(disable: 4503)
//	#pragma warning(disable: 4284)
#else
	#if defined(Q_OS_LINUX)
		// it is assumed that in linux we are using gcc >= 4.0
		#define GKEXPORT __attribute__ ((visibility("default")))
	#else
		#define GKEXPORT 
	#endif
#endif

template <typename T>
struct memSnap{
    T * ptr;
    T * old_ptr;
};


#endif
