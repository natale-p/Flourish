/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#ifdef _WIN32
	#ifdef _V2XFrameworkEXTDLL_DEF
		#define V2XFRAMEWORKEXPORT __declspec(dllexport)
	#else
		#define V2XFRAMEWORKEXPORT __declspec(dllimport)
	#endif
#else
	#ifdef _V2XFrameworkEXTDLL_DEF
		// it is assumed that in linux we are using gcc >= 4.0
		#define V2XFRAMEWORKEXPORT __attribute__ ((visibility("default")))
	#else
		#define V2XFRAMEWORKEXPORT
	#endif
#endif

