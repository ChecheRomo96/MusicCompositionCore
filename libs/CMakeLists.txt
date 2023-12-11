######################################################################################################
# CPSTL 
    
    if(NOT TARGET CPSTL)
        if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/CPSTL)
            set( CPSTL_EXAMPLES FALSE CACHE BOOL "")
            set( CPSTL_TESTING FALSE CACHE BOOL "")
            set( CPSTL_INSTALL FALSE CACHE BOOL "")

            message("Using the CPSTL Source on: MusicCompositonCore/libs/CPSTL")
            add_subdirectory(CPSTL)
        else()

            find_package(CPSTL)

            if(CPSTL_FOUND)
                message("Using the CPSTL Package installed on: ${CMAKE_INSTALL_PREFIX}")
            else()
                message(FATAL_ERROR "CPSTL not found.")
            endif()
        endif()
    endif()

    target_link_libraries( MCC INTERFACE CPSTL )
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