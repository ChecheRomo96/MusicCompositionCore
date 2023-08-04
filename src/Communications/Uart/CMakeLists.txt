######################################################################################################
# Initialize HEADER_LIST as an empty string list

	set( HEADERS_LIST "" )
#
######################################################################################################
# Append Sources and Headers

	list( APPEND MCC_SOURCES "${CMAKE_CURRENT_LIST_DIR}/Uart.cpp")

	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/Uart.h")
#
######################################################################################################
# Add Subdirectories

	if(${MCC_COMPILE_UART_IN_PORT})
		message(STATUS "Compiling MCC::Communications::Uart::InputPort...")
		add_subdirectory(InputPort)
	endif()

	if(${MCC_COMPILE_UART_OUT_PORT})
		message(STATUS "Compiling MCC::Communications::Uart::OutputPort...")
		add_subdirectory(OutputPort)
	endif()

	if(${MCC_COMPILE_UART_DUPLEX_PORT})
		message(STATUS "Compiling MCC::Communications::Uart::DuplexPort...")
		add_subdirectory(DuplexPort)
	endif()

	message(STATUS "Compiling MCC::Communications::Uart::Port...")
	add_subdirectory(Port)
	
	message(STATUS "Compiling MCC::Communications::Uart::SystemPorts...")
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
			DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC/Communications/Uart
		)

	endif()
#
######################################################################################################