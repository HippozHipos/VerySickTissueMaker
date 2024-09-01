#pragma once

#include <signal.h>

#include "diagnostics/Logger.h"

#ifndef SIGTRAP
	#define SIGTRAP 5
#endif
#ifndef VSTM_DEBUG_BREAK
	#define VSTM_DEBUG_BREAK raise(SIGTRAP)
#endif

#ifdef NDEBUG
	#define VSTM_ASSERT(c, ...) 

#elif defined (RELEASE_WITH_DEBUG)
	#define VSTM_ASSERT(c, ...) do { \
			if (!(c)) { \
				VSTM_CD_LOGERROR(__VA_ARGS__); \
				VSTM_DEBUG_BREAK; \
			} \
		} while (0)

#else	
	#define VSTM_ASSERT(c, ...) do { \
		if (!(c)) { \
			VSTM_CD_LOGERROR(__VA_ARGS__); \
			VSTM_DEBUG_BREAK; \
		} \
	} while (0)

#endif

#ifdef NDEBUG
	#define VSTM_ASSERT(c, ...) 

#elif defined (RELEASE_WITH_DEBUG)
	#define VSTM_ASSERT_NO_BREAK(c, ...) do { \
			if (!(c)) { \
				VSTM_CD_LOGERROR(__VA_ARGS__); \
			} \
		} while (0)

#else	
	#define VSTM_ASSERT_NO_BREAK(c, ...) do { \
		if (!(c)) { \
			VSTM_CD_LOGERROR(__VA_ARGS__); \
		} \
	} while (0)

#endif