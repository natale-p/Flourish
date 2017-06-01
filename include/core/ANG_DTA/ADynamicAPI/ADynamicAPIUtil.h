/**
  * Copyright TSS 2017
  *
  * Author: Natale Patriciello <natale.patriciello@aimsun.com>
  */
#pragma once

#include <qglobal.h>

#ifdef _WIN32
	#ifdef _ADYNAMICAPI_DEF
		#define ADYNAMICAPIEXPORT __declspec(dllexport)
	#else
		#define ADYNAMICAPIEXPORT __declspec(dllimport)
	#endif
#else
	#if defined(Q_OS_LINUX)
		// it is assumed that in linux we are using gcc >= 4.0
		#define ADYNAMICAPIEXPORT __attribute__ ((visibility("default")))
	#else
		#define ADYNAMICAPIEXPORT
	#endif
#endif

