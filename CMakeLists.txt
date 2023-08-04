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

	set( MCC_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Compile Configuration

	set(MCC_COMPILE_CORE CACHE BOOL "Compile MCC::Core")
		
		set(MCC_COMPILE_UTILITY_CORE CACHE BOOL "Compile MCC::Core::UtilityCore")	
			set(MCC_COMPILE_ACCUMULATOR CACHE BOOL "Compile MCC::Core::UtilityCore::Accumulator")
		
		set(MCC_COMPILE_MUSICAL_CORE CACHE BOOL "Compile MCC::Core::MusicalCore")
			set(MCC_COMPILE_MUSICAL_NOTE CACHE BOOL "Compile MCC::Core::MusicalCore::Note")
			set(MCC_COMPILE_MUSICAL_INTERVAL CACHE BOOL "Compile MCC::Core::MusicalCore::Interval")	
			set(MCC_COMPILE_MUSICAL_SCALE CACHE BOOL "Compile MCC::Core::MusicalCore::Scale")

		set(MCC_COMPILE_MIDI_CORE CACHE BOOL "Compile MCC::Core::MidiCore")
			set(MCC_COMPILE_MIDI_NOTE CACHE BOOL "Compile MCC::Core::MidiCore::MidiNote")
			set(MCC_COMPILE_MIDI_MESSAGE CACHE BOOL "Compile MCC::Core::MidiCore::MidiMessage")
			

	set(MCC_COMPILE_COMMUNICATIONS CACHE BOOL "Compile MCC::Communications")

		set(MCC_COMPILE_MIDI_PORT CACHE BOOL "Compile MCC::Communications::MidiPort")
	
			set(MCC_COMPILE_UART_MIDI  CACHE BOOL "Compile MCC::Communications::MidiPort::Uart")

			set(MCC_COMPILE_RTMIDI CACHE BOOL "Compile MCC::Communications::MidiPort::RtMidi")

		set(MCC_COMPILE_UART_PORT CACHE BOOL "Compile MCC::Communications::MidiPort::Uart")
			set(MCC_COMPILE_UART_IN_PORT CACHE BOOL "Compile MCC::Communications::Uart::InputPort")
			set(MCC_COMPILE_UART_OUT_PORT CACHE BOOL "Compile MCC::Communications::Uart::OutputPort")
			set(MCC_COMPILE_UART_DUPLEX_PORT CACHE BOOL "Compile MCC::Communications::Uart::DuplexPort")

	set(MCC_BUILD_EXAMPLES CACHE BOOL "Build MCC Examples")
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
