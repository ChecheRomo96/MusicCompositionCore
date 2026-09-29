# MCC compatibility wrapper for RoModularBuild.
# Target profiles continue to set the established MCC_* variables.

include("${CMAKE_CURRENT_LIST_DIR}/MCCRoModularCompatibility.cmake")

mcc_forward_toolchain_cache(MCC_ARM_TOOLCHAIN_ROOT ROMODULAR_ARM_TOOLCHAIN_ROOT
    PATH "" "Optional GNU Arm Embedded installation root")
mcc_forward_toolchain_cache(MCC_ARM_TOOLCHAIN_PREFIX ROMODULAR_ARM_TOOLCHAIN_PREFIX
    STRING "arm-none-eabi" "GNU Arm Embedded compiler prefix")
mcc_forward_toolchain_cache(MCC_ARM_CPU ROMODULAR_ARM_CPU
    STRING "cortex-m3" "Target Arm CPU")
mcc_forward_toolchain_cache(MCC_FLOAT_ABI ROMODULAR_FLOAT_ABI
    STRING "soft" "Target floating-point ABI")
mcc_forward_toolchain_cache(MCC_FPU ROMODULAR_FPU
    STRING "" "Target FPU name")
mcc_forward_toolchain_cache(MCC_ARM_ADDITIONAL_FLAGS ROMODULAR_ARM_ADDITIONAL_FLAGS
    STRING "" "Additional flags shared by C and C++")
mcc_forward_toolchain_cache(MCC_ARM_SYSROOT ROMODULAR_ARM_SYSROOT
    PATH "" "Optional target sysroot containing the C runtime headers and libraries")

set(MCC_ROMODULAR_ROOT
    "${CMAKE_CURRENT_LIST_DIR}/../../tools/RoModularBuild")
set(MCC_ROMODULAR_ARM_TOOLCHAIN
    "${MCC_ROMODULAR_ROOT}/cmake/toolchains/arm-none-eabi.cmake")
if(NOT EXISTS "${MCC_ROMODULAR_ARM_TOOLCHAIN}")
    message(FATAL_ERROR
        "RoModularBuild is not initialized; run "
        "'git submodule update --init --recursive'")
endif()

include("${MCC_ROMODULAR_ARM_TOOLCHAIN}")
