#ifndef MCC_SETUP_H
#define MCC_SETUP_H

	#if defined(ARDUINO) || defined(PSOC_CREATOR) 
		
		// User setup is intended only for platforms in where compilation is not managed with cmake

		#include "MCC_UserSetup.h"
	#endif

#endif//MCC_SETUP_H
