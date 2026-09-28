set(MCC_PITCH_HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/Accidental.h"
    "${CMAKE_CURRENT_LIST_DIR}/ChromaticClass.h"
    "${CMAKE_CURRENT_LIST_DIR}/ChromaticIndex.h"
    "${CMAKE_CURRENT_LIST_DIR}/Letter.h"
    "${CMAKE_CURRENT_LIST_DIR}/Pitch.h"
    "${CMAKE_CURRENT_LIST_DIR}/PitchClass.h")
set(MCC_PITCH_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Pitch.cpp")

target_sources(MCC PRIVATE
    ${MCC_PITCH_HEADERS}
    ${MCC_PITCH_SOURCES})
mcc_stage_headers(${MCC_PITCH_HEADERS})
mcc_add_dox(
    ${MCC_PITCH_HEADERS}
    "${CMAKE_CURRENT_LIST_DIR}/Pitch.dox")

install(FILES ${MCC_PITCH_HEADERS}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/MCC/Pitch"
    CONFIGURATIONS Release)
