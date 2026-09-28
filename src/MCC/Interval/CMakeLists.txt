set(MCC_INTERVAL_HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/Interval.h"
    "${CMAKE_CURRENT_LIST_DIR}/IntervalDirection.h"
    "${CMAKE_CURRENT_LIST_DIR}/IntervalNumber.h"
    "${CMAKE_CURRENT_LIST_DIR}/IntervalQuality.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transposition.h")
set(MCC_INTERVAL_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Interval.cpp")

target_sources(MCC PRIVATE ${MCC_INTERVAL_HEADERS} ${MCC_INTERVAL_SOURCES})
mcc_stage_headers(${MCC_INTERVAL_HEADERS})
mcc_add_dox(
    ${MCC_INTERVAL_HEADERS}
    "${CMAKE_CURRENT_LIST_DIR}/Interval.dox")

install(FILES ${MCC_INTERVAL_HEADERS}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/MCC/Interval"
    CONFIGURATIONS Release)
