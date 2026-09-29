# MCC compatibility wrapper for RoModularBuild.
# Target profiles continue to set the established MCC_* variables.

include("${CMAKE_CURRENT_LIST_DIR}/MCCRoModularCompatibility.cmake")

mcc_forward_toolchain_cache(MCC_AVR_TOOLCHAIN_ROOT ROMODULAR_AVR_TOOLCHAIN_ROOT
    PATH "" "Optional AVR-GCC installation root")
mcc_forward_toolchain_cache(MCC_AVR_TOOLCHAIN_PREFIX ROMODULAR_AVR_TOOLCHAIN_PREFIX
    STRING "avr" "AVR-GCC compiler prefix")
mcc_forward_toolchain_cache(MCC_AVR_MCU ROMODULAR_AVR_MCU
    STRING "" "AVR MCU name accepted by -mmcu")
mcc_forward_toolchain_cache(MCC_AVR_ARCHITECTURE ROMODULAR_AVR_ARCHITECTURE
    STRING "avr" "AVR architecture used as CMAKE_SYSTEM_PROCESSOR metadata")
mcc_forward_toolchain_cache(MCC_AVR_ADDITIONAL_FLAGS ROMODULAR_AVR_ADDITIONAL_FLAGS
    STRING "" "Additional flags shared by C and C++")

set(MCC_ROMODULAR_ROOT
    "${CMAKE_CURRENT_LIST_DIR}/../../tools/RoModularBuild")
set(MCC_ROMODULAR_AVR_TOOLCHAIN
    "${MCC_ROMODULAR_ROOT}/cmake/toolchains/avr-gcc.cmake")
if(NOT EXISTS "${MCC_ROMODULAR_AVR_TOOLCHAIN}")
    message(FATAL_ERROR
        "RoModularBuild is not initialized; run "
        "'git submodule update --init --recursive'")
endif()

include("${MCC_ROMODULAR_AVR_TOOLCHAIN}")
