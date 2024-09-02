#pragma once

#include <assert.h>

#include "Logger.h"

#ifdef NDEBUG 
	#define VSTMR_ASSERT(c, ...)
#else
	#define VSTMR_ASSERT(c, ...) \
	if (!c) \
		VSTM_CD_LOGERROR(__VA_ARGS__); \
		assert(c);	
#endif