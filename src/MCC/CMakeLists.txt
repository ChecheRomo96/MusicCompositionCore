set(MCC_MODULE_HEADERS "")

if(MCC_CORE)
    list(APPEND MCC_MODULE_HEADERS "${CMAKE_CURRENT_LIST_DIR}/Core.h")
endif()

if(MCC_PITCH)
    list(APPEND MCC_MODULE_HEADERS "${CMAKE_CURRENT_LIST_DIR}/Pitch.h")
endif()

if(MCC_INTERVAL)
    list(APPEND MCC_MODULE_HEADERS "${CMAKE_CURRENT_LIST_DIR}/Interval.h")
endif()

if(MCC_TUNING)
    list(APPEND MCC_MODULE_HEADERS "${CMAKE_CURRENT_LIST_DIR}/Tuning.h")
endif()

target_sources(MCC PRIVATE ${MCC_MODULE_HEADERS})
mcc_stage_headers(${MCC_MODULE_HEADERS})
mcc_add_dox(${MCC_MODULE_HEADERS})

install(FILES ${MCC_MODULE_HEADERS}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/MCC"
    CONFIGURATIONS Release)

if(MCC_CORE)
    add_subdirectory(Core)
endif()

if(MCC_PITCH)
    add_subdirectory(Pitch)
endif()

if(MCC_INTERVAL)
    add_subdirectory(Interval)
endif()

if(MCC_TUNING)
    add_subdirectory(Tuning)
endif()
