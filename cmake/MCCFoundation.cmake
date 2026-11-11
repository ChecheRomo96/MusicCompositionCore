# Resolves the Foundation source dependency and defines Foundation::Foundation.
#
# A parent project owns the shared Foundation target. Standalone MCC source
# builds fetch the pinned Foundation revision. MCCConfig.cmake.in keeps the
# find_dependency(Foundation) rule for exported Release packages.

set(MCC_FOUNDATION_VERSION "0.0.1")
set(MCC_FOUNDATION_REPOSITORY "ChecheRomo96/Foundation" CACHE STRING
    "GitHub repository (owner/name) used to fetch Foundation")
option(MCC_FETCH_FOUNDATION
    "Fetch Foundation source when a parent project does not provide it" ON)

set(MCC_FOUNDATION_SOURCE "")
set(MCC_FOUNDATION_RESOLVED_PREFIX "")

if(TARGET Foundation::Foundation)
    set(MCC_FOUNDATION_SOURCE "parent project")
elseif(NOT MCC_FETCH_FOUNDATION)
    message(FATAL_ERROR
        "MCC requires a parent-provided Foundation::Foundation target, or "
        "MCC_FETCH_FOUNDATION=ON.")
else()
    include(FetchContent)
    if(NOT DEFINED FOUNDATION_PLATFORM OR FOUNDATION_PLATFORM STREQUAL "")
        set(FOUNDATION_PLATFORM "${MCC_PLATFORM}" CACHE STRING
            "Foundation target platform identifier")
    endif()
    message(STATUS "Fetching Foundation sources at v${MCC_FOUNDATION_VERSION}")
    FetchContent_Declare(Foundation
        GIT_REPOSITORY "https://github.com/${MCC_FOUNDATION_REPOSITORY}.git"
        GIT_TAG "v${MCC_FOUNDATION_VERSION}"
        GIT_SHALLOW TRUE
        GIT_SUBMODULES "")
    FetchContent_MakeAvailable(Foundation)

    if(NOT TARGET Foundation::Foundation)
        message(FATAL_ERROR
            "Foundation v${MCC_FOUNDATION_VERSION} sources do not define "
            "Foundation::Foundation.")
    endif()
    set(Foundation_PLATFORM "${FOUNDATION_PLATFORM}")

    if(FETCHCONTENT_SOURCE_DIR_FOUNDATION)
        set(MCC_FOUNDATION_SOURCE
            "sources at ${FETCHCONTENT_SOURCE_DIR_FOUNDATION}")
    else()
        set(MCC_FOUNDATION_SOURCE "sources at v${MCC_FOUNDATION_VERSION}")
    endif()
endif()

if((NOT DEFINED Foundation_VERSION OR Foundation_VERSION STREQUAL "") AND
   DEFINED foundation_SOURCE_DIR AND
   EXISTS "${foundation_SOURCE_DIR}/library.properties")
    file(STRINGS "${foundation_SOURCE_DIR}/library.properties"
        foundation_version_line REGEX "^version=" LIMIT_COUNT 1)
    string(REGEX REPLACE "^version=" "" Foundation_VERSION
        "${foundation_version_line}")
endif()

if(DEFINED Foundation_VERSION AND NOT Foundation_VERSION STREQUAL "" AND
   Foundation_VERSION VERSION_LESS MCC_FOUNDATION_VERSION)
    message(FATAL_ERROR
        "MCC requires Foundation ${MCC_FOUNDATION_VERSION}+; resolved "
        "${Foundation_VERSION}.")
endif()

set(MCC_FOUNDATION_RESOLVED_PREFIX "" CACHE INTERNAL
    "Foundation package prefix used by this build")
