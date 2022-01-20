######################################################################################################
# Initialize HEADER_LIST as an empty string list

	set( HEADERS_LIST "" )
#
######################################################################################################
# Append Headers

	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/UtilityCore.h")
#
######################################################################################################
# Add Subdirectories

	if(${MCC_COMPILE_ACCUMULATOR})
		add_subdirectory(Accumulator)
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
			DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC/Core/UtilityCore
		)
	endif()
#
######################################################################################################