option(MCC_EXAMPLES "Enable building examples" OFF)
option(MCC_TESTING "Enable unit testing" OFF)
option(MCC_DOCS "Generate API documentation using Doxygen" OFF)
option(MCC_FULL_BUILD "Enable every MCC module" OFF)
option(MCC_COVERAGE "Enable coverage instrumentation" OFF)

option(MCC_CORE "Enable MCC::Core" ON)
option(MCC_PITCH "Enable MCC pitch primitives" ON)
option(MCC_TUNING "Enable MCC tuning and frequencies (uses float)" ON)

if(MCC_FULL_BUILD)
    set(MCC_CORE ON CACHE BOOL "Enable MCC::Core" FORCE)
    set(MCC_PITCH ON CACHE BOOL "Enable MCC pitch primitives" FORCE)
    set(MCC_TUNING ON CACHE BOOL "Enable MCC tuning and frequencies (uses float)" FORCE)
endif()

if(MCC_TUNING AND NOT MCC_PITCH)
    message(FATAL_ERROR "MCC_TUNING requires MCC_PITCH")
endif()
