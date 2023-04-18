######################################################################################################
# Initialize HEADER_LIST as an empty string list

	set( HEADERS_LIST "" )
#
######################################################################################################
# Append Sources and Headers

	#list( APPEND MCC_SOURCES "${CMAKE_CURRENT_LIST_DIR}/MCC_Core.cpp")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_Communications.h")
#
######################################################################################################
# Add Subdirectories

	if(${MCC_COMPILE_MIDI_PORT})
		message(STATUS "Compiling MCC::Communications::Midi...")
		add_subdirectory(Midi)
	endif()
#
######################################################################################################
# Refresh Sources List at PARENT_SCOPE
	
	set(MCC_SOURCES "${MCC_SOURCES}" PARENT_SCOPE)
#
######################################################################################################
# MCC install process

	if(INSTALL STREQUAL "ON")

		install(
			FILES ${HEADERS_LIST} 
			DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC/Communications
		)

	endif()
#
######################################################################################################