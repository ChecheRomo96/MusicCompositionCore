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

	add_subdirectory(MidiProtocol)

	if(${MCC_COMPILE_MUSICAL_NOTE})
		message(STATUS "Compiling MCC::MusicalNote...")
		add_subdirectory(MusicalNote)
	endif()

	if(${MCC_COMPILE_MUSICAL_INTERVAL})
		message(STATUS "Compiling MCC::MusicalInterval...")
		add_subdirectory(MusicalInterval)
	endif()

	if(${MCC_COMPILE_MUSICAL_SCALE})
		message(STATUS "Compiling MCC::MusicalScale...")
		add_subdirectory(MusicalScale)
	endif()


	if(${MCC_COMPILE_MIDI_NOTE})
		message(STATUS "Compiling MCC::MidiNote...")
		add_subdirectory(MidiNote)
	endif()

	if(${MCC_COMPILE_MIDI_MESSAGE})
		message(STATUS "Compiling MCC::MidiMessage...")
		add_subdirectory(MidiMessage)
	endif()
#
######################################################################################################
# Create the MCC library

	add_library(MCC STATIC ${MCC_SOURCES})
#
######################################################################################################
# Add Compliler Definitions


	if(${MCC_COMPILE_MUSICAL_NOTE})
		target_compile_definitions(MCC PUBLIC MCC_MUSICAL_NOTE_ENABLED)
	endif()

	if(${MCC_COMPILE_MUSICAL_INTERVAL})
		target_compile_definitions(MCC PUBLIC MCC_MUSICAL_INTERVAL_ENABLED)
	endif()

	if(${MCC_COMPILE_MUSICAL_SCALE})
		target_compile_definitions(MCC PUBLIC MCC_MUSICAL_SCALE_ENABLED)
	endif()

	if(${MCC_COMPILE_MUSICAL_CHORD})
		target_compile_definitions(MCC PUBLIC MCC_MUSICAL_CHORD_ENABLED)
	endif()


	if(${MCC_COMPILE_MIDI_NOTE})
		target_compile_definitions(MCC PUBLIC MCC_MIDI_NOTE_ENABLED)
	endif()

	if(${MCC_COMPILE_MIDI_MESSAGE})
		target_compile_definitions(MCC PUBLIC MCC_MIDI_MESSAGE_ENABLED)
	endif()
#
######################################################################################################
# Include directories for install and for build 

	target_include_directories( 
		MCC 
		PUBLIC 
		#$<INSTALL_INTERFACE:include/MCC> 
		"$<BUILD_INTERFACE:${MCC_SRC_DIRECTORY}>"
	)

#
######################################################################################################
# Add libs Subdirectory

	add_subdirectory(${MCC_ROOT_DIRECTORY}/libs ${CMAKE_CURRENT_BINARY_DIR}/libs)
#
######################################################################################################
# Music Composition Core install process

	if(NOT MCC_BUILD_TARGET STREQUAL "Dev" AND NOT MCC_BUILD_TARGET STREQUAL "Submodule")

		install(
			FILES ${HEADERS_LIST} 
			DESTINATION "include/MCC-${MCC_VERSION}"
		)

	endif()
#
######################################################################################################