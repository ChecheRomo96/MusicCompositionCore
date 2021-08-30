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
# Append Sources

	list( APPEND MCC_SOURCES "${CMAKE_CURRENT_LIST_DIR}/MCC.cpp")
#
######################################################################################################
# Append Headers

	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_Setup.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_UserSetup.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_BuildSettings.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_GlobalDefinition.h")
#
######################################################################################################
# Add Subdirectories

	if(MCC_COMPILE_CORE STREQUAL "ON")
		add_subdirectory(Core)
	endif()
#
######################################################################################################
# Create the MCC library (STATIC is not justified tho)

	add_library(MCC STATIC ${MCC_SOURCES})
#
######################################################################################################
# Add Compliler Definitions

	if(MCC_COMPILE_CORE STREQUAL "ON")
		target_compile_definitions(MCC PUBLIC MCC_CORE_ENABLED)
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

	add_subdirectory(${CMAKE_HOME_DIRECTORY}/libs ${CMAKE_CURRENT_BINARY_DIR}/libs)
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