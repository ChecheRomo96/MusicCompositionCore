find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)

    set(DOXYGEN_IN  ${MCC_ROOT_DIRECTORY}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/docs/Doxyfile)
    set(DOXYGEN_HTML_FOOTER
        ${MCC_ROOT_DIRECTORY}/docs/assets/MCCFooter.html)
    set(DOXYGEN_HTML_EXTRA_FILES
        ${MCC_ROOT_DIRECTORY}/docs/assets/MCCDocs.js)

    add_subdirectory(${MCC_ROOT_DIRECTORY}/docs)

    get_target_property(MCC_DOXYGEN_PREDEFS MCC MCC_DOXYGEN_PREDEFS)
    get_target_property(MCC_DOXYGEN_INPUTS MCC MCC_DOXYGEN_INPUTS)

    if(NOT MCC_DOXYGEN_PREDEFS)
        set(MCC_DOXYGEN_PREDEFS "")
    endif()

    if(NOT MCC_DOXYGEN_INPUTS)
        set(MCC_DOXYGEN_INPUTS "")
    endif()

    # Doxygen does not run a C++ compiler, so it cannot infer the language
    # feature-test value selected by the MCC target. Keep C++17 declarations
    # and documentation-only preprocessor paths visible.
    list(APPEND MCC_DOXYGEN_PREDEFS
        DOXYGEN=1
        MCC_CPLUSPLUS=201703L
    )

    string(REPLACE ";" " " DOXYGEN_PREDEFINED "${MCC_DOXYGEN_PREDEFS}")
    string(REPLACE ";" " " DOXYGEN_INPUT "${MCC_DOXYGEN_INPUTS}")

    message(STATUS "Doxygen Predefined:")
    foreach(item IN LISTS MCC_DOXYGEN_PREDEFS)
        message(STATUS "  ${item}")
    endforeach()

    message(STATUS "Doxygen Inputs:")
    foreach(item IN LISTS MCC_DOXYGEN_INPUTS)
        message(STATUS "  ${item}")
    endforeach()

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message(STATUS "Doxygen configuration file created at ${DOXYGEN_OUT}")

    add_custom_target(MCCDocs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${MCC_ROOT_DIRECTORY}
        COMMENT "Generating MCC API documentation with Doxygen"
        VERBATIM
    )

    add_custom_target(docs DEPENDS MCCDocs)

else()
    message(WARNING "Doxygen is required to build the documentation.")
endif()
