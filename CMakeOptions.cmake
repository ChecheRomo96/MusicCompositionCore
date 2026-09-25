option(MCC_EXAMPLES "Enable building examples" OFF)
option(MCC_TESTING "Enable unit testing" OFF)
option(MCC_DOCS "Generate API documentation using Doxygen" OFF)
option(MCC_FULL_BUILD "Enable every MCC module" OFF)
option(MCC_COVERAGE "Enable coverage instrumentation" OFF)

option(MCC_CORE "Enable MCC::Core" ON)

if(MCC_FULL_BUILD)
    set(MCC_CORE ON CACHE BOOL "Enable MCC::Core" FORCE)
endif()
