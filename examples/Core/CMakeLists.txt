######################################################################################################
# Append Utility Core Examples

	if(${MCC_COMPILE_UTILITY_CORE})
		add_subdirectory(UtilityCore)
	endif()
#
######################################################################################################
# Append Musical Core Examples

	if(${MCC_COMPILE_MUSICAL_CORE})
		add_subdirectory(MusicalCore)
	endif()
#
######################################################################################################
# Append Midi Core Examples

	if(${MCC_COMPILE_MIDI_CORE})
		add_subdirectory(MidiCore)
	endif()
#
######################################################################################################


