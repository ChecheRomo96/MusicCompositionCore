add_custom_target(MCCExamples)

function(mcc_add_example TARGET_NAME)
    if(ARGC LESS 2)
        message(FATAL_ERROR
            "mcc_add_example(${TARGET_NAME}) requires at least one source file")
    endif()

    add_executable(${TARGET_NAME} ${ARGN})
    target_link_libraries(${TARGET_NAME} PRIVATE MCC::MCC)
    set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")
    add_dependencies(MCCExamples ${TARGET_NAME})

    install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/examples"
        CONFIGURATIONS Release
        COMPONENT Examples)
endfunction()

set(MCC_DESKTOP_EXAMPLES_SUPPORTED OFF)
if(APPLE OR WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(MCC_DESKTOP_EXAMPLES_SUPPORTED ON)
endif()

add_subdirectory(MCC)

set(MCC_EXAMPLES_LAUNCHER_DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/launchers")

if(APPLE)
    set(MCC_EXAMPLES_LAUNCHER
        "${MCC_EXAMPLES_LAUNCHER_DIRECTORY}/MCCExamples.command")
    configure_file(
        "${MCC_ROOT_DIRECTORY}/examples/Launchers/macOS.command.in"
        "${MCC_EXAMPLES_LAUNCHER}"
        @ONLY NEWLINE_STYLE UNIX)
    install(PROGRAMS "${MCC_EXAMPLES_LAUNCHER}"
        DESTINATION "${CMAKE_INSTALL_BINDIR}/examples"
        CONFIGURATIONS Release COMPONENT Examples)
elseif(WIN32)
    set(MCC_EXAMPLES_LAUNCHER
        "${MCC_EXAMPLES_LAUNCHER_DIRECTORY}/MCCExamples.cmd")
    configure_file(
        "${MCC_ROOT_DIRECTORY}/examples/Launchers/Windows.cmd.in"
        "${MCC_EXAMPLES_LAUNCHER}"
        @ONLY NEWLINE_STYLE WIN32)
    install(PROGRAMS "${MCC_EXAMPLES_LAUNCHER}"
        DESTINATION "${CMAKE_INSTALL_BINDIR}/examples"
        CONFIGURATIONS Release COMPONENT Examples)
endif()
