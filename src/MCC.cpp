#include "MCC.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start

	void MCC::Start()
	{
		#if defined(ARDUINO)
			Arduino_Start();
		#elif defined(PSOC_CREATOR)
			PSOC_Start();
        #else
            CPP_Start();
		#endif

		Core::Start();
		//Communications::Start();
	}

	#if defined(ARDUINO)

		void MCC::Arduino_Start()
		{
			#if defined(DEBUG)
				Serial.print("Music Composition Core Version = ");
				Serial.println(MCC_VERSION);
				Serial.println();
            #endif
		}

	#elif defined(PSOC_CREATOR)

		void MCC::PSOC_Start()
		{
			#if defined(DEBUG)
            #endif
		}

	#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__APPLE__) || defined(linux)

	    std::chrono::high_resolution_clock::time_point MCC::StartTime;

		void MCC::CPP_Start()
		{
			StartTime = std::chrono::high_resolution_clock::now();
			#if defined(DEBUG)
            	std::cout<<"Music Composition Core Version = "<<MCC_VERSION<<"\n\n";
            #endif
		}

	#endif
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Service

	void MCC::Service()
	{
		//MCC::ServiceHandler::SystemHandler.Service();
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
