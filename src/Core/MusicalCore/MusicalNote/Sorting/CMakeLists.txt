# Initialize HEADER_LIST as an empty string list
set( HEADERS_LIST "" )

# Append Headers
list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/MusicalNote_Sorting.h")

# Add Subdirectories
add_subdirectory(AccidentalClass)
add_subdirectory(LetterClass)
add_subdirectory(NoteClass)
add_subdirectory(PitchClass)

# Refresh Sources List at PARENT_SCOPE
set(MCC_SOURCES "${MCC_SOURCES}" PARENT_SCOPE)

# MCC install process
if(INSTALL STREQUAL "ON")

	install(
		FILES ${HEADERS_LIST} 
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include/MCC/Core/MusicalCore/MusicalNote/Sorting
	)

endif()
