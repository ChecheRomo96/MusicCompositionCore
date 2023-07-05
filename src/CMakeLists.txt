######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

	set( MCC_SRC_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Initialize MCC_SOURCES and HEADER_LIST as an empty string list

	set( MCC_SOURCES "" )
	set( HEADERS_LIST "" )
#
######################################################################################################
# Append Sources and Headers

	list( APPEND MCC_SOURCES "${CMAKE_CURRENT_LIST_DIR}/MCC.cpp")

	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_Setup.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_UserSetup.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_BuildSettings.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_GlobalDefinition.h")
#
######################################################################################################
# Add Subdirectories

	if(${MCC_COMPILE_CORE})
		message(STATUS "Compiling MCC::Core...")
		add_subdirectory(Core)
	endif()

	if(${MCC_COMPILE_COMMUNICATIONS})
		message(STATUS "Compiling MCC::Communications...")
		add_subdirectory(Communications)
	endif()
#
######################################################################################################
# Create the MCC library (STATIC is not justified tho)

	add_library(MCC STATIC ${MCC_SOURCES})
#
######################################################################################################
# Add Compliler Definitions

	if(${MCC_COMPILE_CORE})
		target_compile_definitions(MCC PUBLIC MCC_CORE_ENABLED)

		if(${MCC_COMPILE_UTILITY_CORE})
			target_compile_definitions(MCC PUBLIC MCC_UTILITY_CORE_ENABLED)

			if(${MCC_COMPILE_ACCUMULATOR})
				target_compile_definitions(MCC PUBLIC MCC_ACCUMULATOR_ENABLED)
			endif()

		endif()

		if(${MCC_COMPILE_MUSICAL_CORE})
			target_compile_definitions(MCC PUBLIC MCC_MUSICAL_CORE_ENABLED)

			if(${MCC_COMPILE_MUSICAL_NOTE})
				target_compile_definitions(MCC PUBLIC MCC_MUSICAL_NOTE_ENABLED)
			endif()

			if(${MCC_COMPILE_MUSICAL_INERVAL})
				target_compile_definitions(MCC PUBLIC MCC_MUSICAL_INTERVAL_ENABLED)
			endif()

			if(${MCC_COMPILE_MUSICAL_SCALE})
				target_compile_definitions(MCC PUBLIC MCC_MUSICAL_SCALE_ENABLED)
			endif()
		endif()

		if(${MCC_COMPILE_MIDI_CORE})
			target_compile_definitions(MCC PUBLIC MCC_MIDI_CORE_ENABLED)

			if(${MCC_COMPILE_MIDI_NOTE})
				target_compile_definitions(MCC PUBLIC MCC_MIDI_NOTE_ENABLED)
			endif()

		endif()

	endif()


	if(${MCC_COMPILE_COMMUNICATIONS})
		target_compile_definitions(MCC PUBLIC MCC_COMMUNICATIONS_ENABLED)

		if(${MCC_COMPILE_UART_PORT})
			target_compile_definitions(MCC PUBLIC MCC_UART_PORT_ENABLED)

			if(${MCC_COMPILE_UART_IN_PORT})
				target_compile_definitions(MCC PUBLIC MCC_UART_IN_ENABLED)
			endif()

			if(${MCC_COMPILE_UART_OUT_PORT})
				target_compile_definitions(MCC PUBLIC MCC_UART_OUT_ENABLED)
			endif()

			if(${MCC_COMPILE_UART_DUPLEX_PORT})
				target_compile_definitions(MCC PUBLIC MCC_UART_DUPLEX_ENABLED)
			endif()
		endif()
		
		if(${MCC_COMPILE_MIDI_PORT})
			target_compile_definitions(MCC PUBLIC MCC_MIDI_PORT_ENABLED)

			if(${MCC_COMPILE_UART_MIDI})
				target_compile_definitions(MCC PUBLIC MCC_UART_MIDI_ENABLED)
			endif()

			if(${MCC_COMPILE_RTMIDI})
				target_compile_definitions(MCC PUBLIC MCC_RTMIDI_ENABLED)
			endif()

		endif()


	endif()
#
######################################################################################################
# Include directories for install and for build 

	target_include_directories( 
		MCC PUBLIC 
		$<INSTALL_INTERFACE:include/MCC> 
		$<BUILD_INTERFACE:${MCC_SRC_DIRECTORY}> 
	)

#
######################################################################################################
# Add libs Subdirectory

	add_subdirectory(${MCC_ROOT_DIRECTORY}/libs ${CMAKE_CURRENT_BINARY_DIR}/libs)
#
######################################################################################################
# Music Composition Core install process

	if(INSTALL STREQUAL "ON")

		install(
			FILES ${HEADERS_LIST} 
			DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC 
		)

		install(
			TARGETS MCC 
			EXPORT MCCExport
			DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/MCC
		)

		install(
			EXPORT MCCExport
			FILE MCC-config.cmake
			DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/MCC
		)

	endif()
#
######################################################################################################