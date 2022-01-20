# Initialize HEADER_LIST as an empty string list
	set( HEADERS_LIST "" )

# Append Headers
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MusicalCore.h")

# Add Subdirectories

	if(${MCC_COMPILE_MUSICAL_NOTE})
		message(STATUS "Compiling MCC::Core::MusicalCore::MusicalNote...")
		add_subdirectory(MusicalNote)
	endif()

	if(${MCC_COMPILE_MUSICAL_INTERVAL})
		message(STATUS "Compiling MCC::Core::MusicalCore::MusicalInterval...")
		add_subdirectory(MusicalInterval)
	endif()

	if(${MCC_COMPILE_MUSICAL_SCALE})
		message(STATUS "Compiling MCC::Core::MusicalCore::MusicalScale...")
		add_subdirectory(MusicalScale)
	endif()


# Refresh Sources List at PARENT_SCOPE
	set(MCC_SOURCES "${MCC_SOURCES}" PARENT_SCOPE)

# MCC install process
	if(INSTALL STREQUAL "ON")

		install(
			FILES ${HEADERS_LIST} 
			DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC/Core/MusicalCore
		)

	endif()
