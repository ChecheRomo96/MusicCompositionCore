# Initialize HEADER_LIST as an empty string list
set( HEADERS_LIST "" )

# Append Sources
list( APPEND MCC_SOURCES "${CMAKE_CURRENT_LIST_DIR}/ScaleFlash.cpp")

# Append Headers
list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/ScaleFlash.h")
list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/ScaleFlash_Definitions.h")

# Add Subdirectories
add_subdirectory(ScaleDefinitions)
add_subdirectory(ScaleArrays)

# Refresh Sources List at PARENT_SCOPE
set(MCC_SOURCES "${MCC_SOURCES}" PARENT_SCOPE)

# MCC install process
if(INSTALL STREQUAL "ON")

	install(
		FILES ${HEADERS_LIST} 
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC/Core/MusicalCore/MusicalScale/Flash
	)

endif()
