######################################################################################################
# Setting up the project

	##################################################################################################
	# C Make Minimum Version
		
		cmake_minimum_required(VERSION 3.14)
	#
	##################################################################################################
	# Project Name Version and Languaje, print and add preprocessor flag
		
		project(MCC VERSION 0.0.1 LANGUAGES CXX)
		message("Building ${CMAKE_PROJECT_NAME} Version = ${CMAKE_PROJECT_VERSION}...")

		string(TOUPPER ${CMAKE_PROJECT_NAME} PROJECT_NAME_UPPER)
		add_definitions( -D${PROJECT_NAME_UPPER}_VERSION="${CMAKE_PROJECT_VERSION}" )
	#
	##################################################################################################
	# Set up C++ Version

		set(CMAKE_CXX_STANDARD 14) 
		set(CMAKE_CXX_STANDARD_REQUIRED ON)
	#
	##################################################################################################
#
######################################################################################################
# Compile Configuration

	set(MCC_COMPILE_CORE TRUE CACHE BOOL "Compile MCC::Core")
		
		set(MCC_COMPILE_UTILITY_CORE TRUE CACHE BOOL "Compile MCC::Core::UtilityCore")	
			set(MCC_COMPILE_ACCUMULATOR TRUE CACHE BOOL "Compile MCC::Core::UtilityCore::Accumulator")
		
		set(MCC_COMPILE_MUSICAL_CORE TRUE CACHE BOOL "Compile MCC::Core::MusicalCore")
			set(MCC_COMPILE_MUSICAL_NOTE TRUE CACHE BOOL "Compile MCC::Core::MusicalCore::Note")
			set(MCC_COMPILE_MUSICAL_INTERVAL TRUE CACHE BOOL "Compile MCC::Core::MusicalCore::Interval")	
			set(MCC_COMPILE_MUSICAL_SCALE TRUE CACHE BOOL "Compile MCC::Core::MusicalCore::Scale")	
	

	set(MCC_BUILD_EXAMPLES TRUE CACHE BOOL "Build MCC Examples")
#
######################################################################################################
# Set RtMidi Status (MIDI Interface for desktop builds)

	set(MCC_RTMIDI_STATUS TRUE)
#
######################################################################################################
# Append Source

	add_subdirectory(src)
#
######################################################################################################
# Append Examples

	if( ${MCC_BUILD_EXAMPLES} )
		message("Building ${CMAKE_PROJECT_NAME} Examples...")
		add_subdirectory(examples)
	endif()
#
######################################################################################################
