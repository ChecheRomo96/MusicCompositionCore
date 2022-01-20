######################################################################################################
# Initialize HEADER_LIST as an empty string list

	set( HEADERS_LIST "" )
#
######################################################################################################
# Append Sources and Headers

	list( APPEND MCC_SOURCES "${CMAKE_CURRENT_LIST_DIR}/MCC_Core.cpp")

	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MCC_Core.h")
#
######################################################################################################
# Add Subdirectories

	if(${MCC_COMPILE_UTILITY_CORE})
		message(STATUS "Compiling MCC::Core::UtilityCore...")
		add_definitions( -DMCC_COMPILE_UTILITY_CORE)
		add_subdirectory(UtilityCore)
	endif()

	if(${MCC_COMPILE_MUSICAL_CORE})
		message(STATUS "Compiling MCC::Core::MusicalCore...")
		add_definitions( -DMCC_COMPILE_MUSICAL_CORE)
		add_subdirectory(MusicalCore)
	endif()
#
######################################################################################################
# Refresh Sources List at PARENT_SCOPE
	
	set(MCC_SOURCES "${MCC_SOURCES}" PARENT_SCOPE)
#
######################################################################################################
# Add Compliler Definitions

	if(MCC_COMPILE_UTILITY_CORE)
		#target_compile_definitions(MCC PUBLIC MCC_UTILITY_CORE_ENABLED)
	endif()

	if(MCC_COMPILE_MUSICAL_CORE)
		#target_compile_definitions(MCC PUBLIC MCC_MUSICAL_CORE_ENABLED)
	endif()
#
######################################################################################################
# MCC install process

	if(INSTALL STREQUAL "ON")

		install(
			FILES ${HEADERS_LIST} 
			DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC/Core
		)

	endif()
#
######################################################################################################