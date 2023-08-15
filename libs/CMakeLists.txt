######################################################################################################
# CPString 
	
	if(NOT TARGET CPString)
		if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/CPString)
			set( CPSTRING_BUILD_EXAMPLES FALSE CACHE BOOL "")
			set( CPSTRING_INSTALL FALSE CACHE BOOL "")

			message("Using the CPStirng Source on: MusicCompositonCore/libs/CPString")
			add_subdirectory(CPString)
		else()

			find_package(CPString)

			if(CPString_FOUND)
				message("Using the CPStirng Package installed on: ${CMAKE_INSTALL_PREFIX}")
			else()
				message(FATAL_ERROR "CPString not found.")
			endif()
		endif()
	endif()

	target_link_libraries( MCC PUBLIC CPString )
#
######################################################################################################
# CPVector
	
	if(NOT TARGET CPVector)
		if(find_package(CPVector))
		
			if(CPVector_FOUND)
				message("Using the CPVector Package installed on: ${CMAKE_INSTALL_PREFIX}")
			else()
				message(FATAL_ERROR "CPVector not found.")
			endif()
			
		elseif(EXISTS ${CMAKE_CURRENT_LIST_DIR}/CPVector)

			set( CPVECTOR_BUILD_EXAMPLES FALSE CACHE BOOL "")
			set( CPVECTOR_INSTALL FALSE CACHE BOOL "")

			message("Using the CPVector Source on: MusicCompositonCore/libs/CPVector")
			add_subdirectory(CPVector)

		endif()
	endif()

	target_link_libraries(MCC PUBLIC CPVector)
#		
######################################################################################################
# RtMidi
	
	if(MCC_COMPILE_RTMIDI)

		option(RTMIDI_BUILD_TESTING "Build test programs" OFF)

		if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/rtmidi)
			set( BUILD_EXAMPLES "OFF" )
			set( INSTALL "OFF" )
			set( RTMIDI_BUILD_TESTING "OFF" )
			message("Using the RtMidi Source on: MusicCompositonCore/libs/rtmidi")
			
			add_subdirectory(rtmidi)
		else()

			find_package(rtmidi)

			if(rtmidi_FOUND)
				message("Using the RtMidi Package installed on: ${CMAKE_INSTALL_PREFIX}")
			else()
				message(FATAL_ERROR "RtMidi not found.")
			endif()
		endif()

		target_link_libraries(MCC PUBLIC rtmidi)
	endif()
#
######################################################################################################