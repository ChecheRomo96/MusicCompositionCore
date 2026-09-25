# Generic GNU Arm Embedded toolchain.
# Target profile files set MCC_ARM_CPU, MCC_FLOAT_ABI, and
# optionally MCC_FPU before including this file.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(MCC_ARM_TOOLCHAIN_ROOT "" CACHE PATH
    "Optional GNU Arm Embedded installation root")
set(MCC_ARM_TOOLCHAIN_PREFIX "arm-none-eabi" CACHE STRING
    "GNU Arm Embedded compiler prefix")
set(MCC_ARM_CPU "cortex-m3" CACHE STRING "Target Arm CPU")
set(MCC_FLOAT_ABI "soft" CACHE STRING "Target floating-point ABI")
set(MCC_FPU "" CACHE STRING "Target FPU name")
set(MCC_ARM_ADDITIONAL_FLAGS "" CACHE STRING
    "Additional flags shared by C and C++")
set(MCC_ARM_SYSROOT "" CACHE PATH
    "Optional target sysroot containing the C runtime headers and libraries")

set(CMAKE_SYSTEM_PROCESSOR "${MCC_ARM_CPU}")

if(NOT MCC_ARM_SYSROOT STREQUAL "")
    set(CMAKE_SYSROOT "${MCC_ARM_SYSROOT}")
endif()

set(_mcc_arm_program_hints)
if(NOT MCC_ARM_TOOLCHAIN_ROOT STREQUAL "")
    list(APPEND _mcc_arm_program_hints
        "${MCC_ARM_TOOLCHAIN_ROOT}/bin"
    )
endif()

find_program(CMAKE_C_COMPILER
    NAMES "${MCC_ARM_TOOLCHAIN_PREFIX}-gcc"
    HINTS ${_mcc_arm_program_hints}
    REQUIRED
)
find_program(CMAKE_CXX_COMPILER
    NAMES "${MCC_ARM_TOOLCHAIN_PREFIX}-g++"
    HINTS ${_mcc_arm_program_hints}
    REQUIRED
)
find_program(CMAKE_AR
    NAMES "${MCC_ARM_TOOLCHAIN_PREFIX}-ar"
    HINTS ${_mcc_arm_program_hints}
    REQUIRED
)
find_program(CMAKE_RANLIB
    NAMES "${MCC_ARM_TOOLCHAIN_PREFIX}-ranlib"
    HINTS ${_mcc_arm_program_hints}
    REQUIRED
)

if(MCC_FLOAT_ABI STREQUAL "hard" AND MCC_FPU STREQUAL "")
    message(FATAL_ERROR "MCC_FPU is required when MCC_FLOAT_ABI=hard")
endif()

set(_mcc_arm_flags
    "-mcpu=${MCC_ARM_CPU} -mthumb -mfloat-abi=${MCC_FLOAT_ABI}"
)
if(NOT MCC_FPU STREQUAL "")
    string(APPEND _mcc_arm_flags " -mfpu=${MCC_FPU}")
endif()
if(NOT MCC_ARM_ADDITIONAL_FLAGS STREQUAL "")
    string(APPEND _mcc_arm_flags " ${MCC_ARM_ADDITIONAL_FLAGS}")
endif()

set(_mcc_common_flags
    "${_mcc_arm_flags} -ffunction-sections -fdata-sections"
)

set(CMAKE_C_FLAGS_INIT "${_mcc_common_flags}")
set(CMAKE_CXX_FLAGS_INIT
    "${_mcc_common_flags} -fno-exceptions -fno-rtti -fcheck-new"
)
set(CMAKE_EXE_LINKER_FLAGS_INIT
    "${_mcc_arm_flags} -Wl,--gc-sections"
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
