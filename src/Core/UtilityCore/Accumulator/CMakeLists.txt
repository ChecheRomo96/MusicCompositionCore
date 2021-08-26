# Initialize HEADER_LIST as an empty string list
set( HEADERS_LIST "" )

# Append Headers
list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_Accumulator.h")

# MCC install process
if(INSTALL STREQUAL "ON")

	install(
		FILES ${HEADERS_LIST} 
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC/Core/UtilityCore/Accumulator
	)

endif()