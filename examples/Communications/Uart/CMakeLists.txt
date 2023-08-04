######################################################################################################
# Append Uart Port Examples

	add_subdirectory(Port)
#
#######################################################################################################
# Append Uart Input Port Examples

	if(${MCC_COMPILE_UART_IN_PORT})
		add_subdirectory(InputPort)
	endif()
#
######################################################################################################
# Append Uart Output Port Examples

	if(${MCC_COMPILE_UART_OUT_PORT})
		add_subdirectory(OutputPort)
	endif()
#
######################################################################################################