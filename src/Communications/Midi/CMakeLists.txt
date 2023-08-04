######################################################################################################
# Initialize HEADER_LIST as an empty string list

	set( HEADERS_LIST "" )
#
######################################################################################################
# Append Sources and Headers

	list( APPEND MCC_SOURCES "${CMAKE_CURRENT_LIST_DIR}/MCC_Midi.cpp")

	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_Midi.h")
#
######################################################################################################
# Add Subdirectories

	if(${MCC_COMPILE_UART_MIDI})
		message(STATUS "Compiling MCC::Communications::Midi::UartMidi...")
		add_subdirectory(UartMidi)
	endif()

	message(STATUS "Compiling MCC::Communications::Midi::Port...")
	add_subdirectory(Port)
	
	message(STATUS "Compiling MCC::Communications::Midi::SystemPorts...")
	add_subdirectory(SystemPorts)
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
			DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC/Communications/Midi
		)

	endif()
#
######################################################################################################