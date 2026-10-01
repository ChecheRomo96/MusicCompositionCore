cmake_minimum_required(VERSION 3.25)

project(MCC VERSION 0.5.1 LANGUAGES C CXX)

set(MCC_REQUIRED_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(MCC_ROOT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}")
set(MCC_PLATFORM "desktop" CACHE STRING "MCC target platform identifier")
set(MCC_EXPECTED_SYSTEM_PROCESSOR "" CACHE STRING
    "Regular expression for the expected target processor")

file(STRINGS "${MCC_ROOT_DIRECTORY}/library.properties"
    MCC_ARDUINO_VERSION_LINE REGEX "^version=" LIMIT_COUNT 1)
string(REGEX REPLACE "^version=" "" MCC_ARDUINO_VERSION
    "${MCC_ARDUINO_VERSION_LINE}")
if(NOT MCC_ARDUINO_VERSION STREQUAL PROJECT_VERSION)
    message(FATAL_ERROR
        "Version mismatch: CMake declares ${PROJECT_VERSION}, but "
        "library.properties declares ${MCC_ARDUINO_VERSION}")
endif()

file(STRINGS "${MCC_ROOT_DIRECTORY}/src/MCC_BuildSettings.h"
    MCC_SOURCE_VERSION_LINE
    REGEX "^[ \t]*#define[ \t]+MCC_VERSION[ \t]+\"[^\"]+\""
    LIMIT_COUNT 1)
if(NOT MCC_SOURCE_VERSION_LINE MATCHES "\"([^\"]+)\"")
    message(FATAL_ERROR "MCC_BuildSettings.h does not declare MCC_VERSION")
endif()
if(NOT CMAKE_MATCH_1 STREQUAL PROJECT_VERSION)
    message(FATAL_ERROR
        "Version mismatch: CMake declares ${PROJECT_VERSION}, but "
        "MCC_BuildSettings.h declares ${CMAKE_MATCH_1}")
endif()

if(MCC_EXPECTED_SYSTEM_PROCESSOR AND
   NOT CMAKE_SYSTEM_PROCESSOR MATCHES "${MCC_EXPECTED_SYSTEM_PROCESSOR}")
    message(FATAL_ERROR
        "Preset '${MCC_PLATFORM}' expects processor "
        "'${MCC_EXPECTED_SYSTEM_PROCESSOR}', but CMake detected "
        "'${CMAKE_SYSTEM_PROCESSOR}'")
endif()

include(cmake/MCCFoundation.cmake)

message(STATUS "Building MCC Version = ${PROJECT_VERSION}")
message(STATUS "Required C++ standard = C++${MCC_REQUIRED_CXX_STANDARD}")
message(STATUS "System      = ${CMAKE_SYSTEM_NAME}")
message(STATUS "Processor   = ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CXX ID      = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Foundation  = ${Foundation_VERSION} (${Foundation_PLATFORM}) from ${MCC_FOUNDATION_SOURCE}")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(cmake/MCCHelpers.cmake)
include(CMakeOptions.cmake)

if(MCC_COVERAGE)
    message(STATUS "Enabling code coverage")
    set(MCC_COVERAGE_FLAGS "--coverage -O0 -g")
    string(APPEND CMAKE_C_FLAGS_DEBUG " ${MCC_COVERAGE_FLAGS}")
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " ${MCC_COVERAGE_FLAGS}")
    string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " ${MCC_COVERAGE_FLAGS}")
endif()

add_subdirectory(src)
mcc_add_macro(PUBLIC MCC_VERSION="${PROJECT_VERSION}")

if(MCC_EXAMPLES)
    add_subdirectory(examples)
endif()

add_custom_target(MCCExportArtifacts)
add_dependencies(MCCExportArtifacts MCC)
if(TARGET MCCExamples)
    add_dependencies(MCCExportArtifacts MCCExamples)
endif()

if(MCC_DOCS)
    mcc_add_dox("${MCC_ROOT_DIRECTORY}/README.md")
    include(cmake/BuildDocs.cmake)
endif()

if(MCC_TESTING)
    include(cmake/BuildTests.cmake)
    add_subdirectory(tests)
    mcc_enable_warnings(MCC)
endif()

configure_package_config_file(
    "${MCC_ROOT_DIRECTORY}/cmake/MCCConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/MCCConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MCC")

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MCCConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

configure_file(
    "${MCC_ROOT_DIRECTORY}/cmake/MCCBuildInfo.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/MCCBuildInfo.cmake"
    @ONLY)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MCCConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MCCConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MCCBuildInfo.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MCC"
    CONFIGURATIONS Release)
