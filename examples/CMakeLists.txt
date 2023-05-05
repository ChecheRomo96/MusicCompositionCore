######################################################################################################
# Append Build Test

	add_subdirectory(MCC_BuildTest)
#
######################################################################################################
# Append Core Examples

	if(${MCC_COMPILE_CORE})
		add_subdirectory(Core)
	endif()
#
######################################################################################################
# Append Communications Examples

	if(${MCC_COMPILE_COMMUNICATIONS})
		add_subdirectory(Communications)
	endif()
#
######################################################################################################
# Append Code Testing Executable

	add_subdirectory(MCC_CodeTesting)
#
######################################################################################################