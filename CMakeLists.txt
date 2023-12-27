	######################################################################################################
# Setting up the project

	##################################################################################################
	# C Make Minimum Version
		
		cmake_minimum_required(VERSION 3.14)
	#
	##################################################################################################
	# Project Name Version and Languaje, print and add preprocessor flag
		
		project(MCC VERSION 0.0.1 LANGUAGES CXX)
		message(STATUS "Building ${PROJECT_NAME} Version = ${PROJECT_VERSION}...")

		string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
		add_definitions( -D${PROJECT_NAME_UPPER}_VERSION="${PROJECT_VERSION}" )
	#
	##################################################################################################
	# Set up C++ Version

		set(CMAKE_CXX_STANDARD 17) 
		set(CMAKE_CXX_STANDARD_REQUIRED ON)
	#
	##################################################################################################
#
######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

	set( ${PROJECT_NAME_UPPER}_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Compile Configuration

	set(MCC_COMPILE_MUSICAL_CORE CACHE BOOL "Compile MCC::Core::MusicalCore")
		set(MCC_COMPILE_MUSICAL_NOTE CACHE BOOL "Compile MCC::Core::MusicalCore::Note")
		set(MCC_COMPILE_MUSICAL_INTERVAL CACHE BOOL "Compile MCC::Core::MusicalCore::Interval")	
		set(MCC_COMPILE_MUSICAL_SCALE CACHE BOOL "Compile MCC::Core::MusicalCore::Scale")

	set(MCC_COMPILE_MIDI_CORE CACHE BOOL "Compile MCC::Core::MidiCore")
		set(MCC_COMPILE_MIDI_NOTE CACHE BOOL "Compile MCC::Core::MidiCore::MidiNote")
		set(MCC_COMPILE_MIDI_MESSAGE CACHE BOOL "Compile MCC::Core::MidiCore::MidiMessage")
			

	set(MCC_BUILD_EXAMPLES CACHE BOOL "Build MCC Examples")
	set(MCC_TESTING CACHE BOOL "Build MCC Unit Tests")
#
######################################################################################################
# Set RtMidi Status (MIDI Interface for desktop builds)

	set(MCC_RTMIDI_STATUS CACHE BOOL "Build MCC Examples")
#
######################################################################################################
# Append Source

	add_subdirectory(src)
#
######################################################################################################
# Append Examples

	if( ${MCC_BUILD_EXAMPLES} )
		message("Building ${PROJECT_NAME} Examples...")
		add_subdirectory(examples)
	endif()
#
######################################################################################################
# Append Tests

	if( ${MCC_TESTING} )
		message("Building ${CMAKE_PROJECT_NAME} Tests...")

		cmake_policy(SET CMP0135 NEW)

		include(FetchContent)

		FetchContent_Declare(
		  googletest
		  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
		)
		# For Windows: Prevent overriding the parent project's compiler/linker settings
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
		FetchContent_MakeAvailable(googletest)

		enable_testing()
		include(GoogleTest)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${${PROJECT_NAME_UPPER}_ROOT_DIRECTORY}/bin")
		add_subdirectory(tests)
	endif()
#
######################################################################################################

