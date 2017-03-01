//-*-Mode: C++;-*-
#pragma once

//SDK

#ifdef _WIN32
#ifdef _V2XFrameworkEXTDLL_DEF
#define V2XFRAMEWORKEXPORT __declspec(dllexport)
	#else
#ifdef _V2XFrameworkEXTDLL_DEF
#define V2XFRAMEWORKEXPORT __declspec(dllexport)
		#else
#define V2XFRAMEWORKEXPORT __declspec(dllimport)
		#endif
	#endif

	#pragma warning(disable: 4251)
	#pragma warning(disable: 4786)
	#pragma warning(disable: 4503)
//	#pragma warning(disable: 4284)
#else
#define V2XFRAMEWORKEXPORT
#endif
