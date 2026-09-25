# Generic AVR-GCC toolchain.
# Target profile files set MCC_AVR_MCU and MCC_AVR_ARCHITECTURE
# before including this file.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(MCC_AVR_TOOLCHAIN_ROOT "" CACHE PATH
    "Optional AVR-GCC installation root")
set(MCC_AVR_TOOLCHAIN_PREFIX "avr" CACHE STRING
    "AVR-GCC compiler prefix")
set(MCC_AVR_MCU "" CACHE STRING
    "AVR MCU name accepted by -mmcu")
set(MCC_AVR_ARCHITECTURE "avr" CACHE STRING
    "AVR architecture used as CMAKE_SYSTEM_PROCESSOR metadata")
set(MCC_AVR_ADDITIONAL_FLAGS "" CACHE STRING
    "Additional flags shared by C and C++")

if(MCC_AVR_MCU STREQUAL "")
    message(FATAL_ERROR
        "MCC_AVR_MCU must name the exact AVR target (for example atmega328p)"
    )
endif()

set(CMAKE_SYSTEM_PROCESSOR "${MCC_AVR_ARCHITECTURE}")

set(_mcc_avr_program_hints)
if(NOT MCC_AVR_TOOLCHAIN_ROOT STREQUAL "")
    list(APPEND _mcc_avr_program_hints
        "${MCC_AVR_TOOLCHAIN_ROOT}/bin"
    )
endif()

find_program(CMAKE_C_COMPILER
    NAMES "${MCC_AVR_TOOLCHAIN_PREFIX}-gcc"
    HINTS ${_mcc_avr_program_hints}
    REQUIRED
)
find_program(CMAKE_CXX_COMPILER
    NAMES "${MCC_AVR_TOOLCHAIN_PREFIX}-g++"
    HINTS ${_mcc_avr_program_hints}
    REQUIRED
)
find_program(CMAKE_AR
    NAMES "${MCC_AVR_TOOLCHAIN_PREFIX}-ar"
    HINTS ${_mcc_avr_program_hints}
    REQUIRED
)
find_program(CMAKE_RANLIB
    NAMES "${MCC_AVR_TOOLCHAIN_PREFIX}-ranlib"
    HINTS ${_mcc_avr_program_hints}
    REQUIRED
)

set(_mcc_avr_flags "-mmcu=${MCC_AVR_MCU}")
if(NOT MCC_AVR_ADDITIONAL_FLAGS STREQUAL "")
    string(APPEND _mcc_avr_flags
        " ${MCC_AVR_ADDITIONAL_FLAGS}"
    )
endif()

set(_mcc_avr_common_flags
    "${_mcc_avr_flags} -ffunction-sections -fdata-sections"
)

set(CMAKE_C_FLAGS_INIT "${_mcc_avr_common_flags}")
set(CMAKE_CXX_FLAGS_INIT
    "${_mcc_avr_common_flags} -fno-exceptions -fno-rtti -fcheck-new"
)
set(CMAKE_EXE_LINKER_FLAGS_INIT
    "${_mcc_avr_flags} -Wl,--gc-sections"
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
