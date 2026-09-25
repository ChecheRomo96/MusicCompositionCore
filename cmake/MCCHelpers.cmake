function(mcc_add_macro visibility)
    target_compile_definitions(MCC ${visibility} ${ARGN})
    set_property(TARGET MCC APPEND PROPERTY MCC_DOXYGEN_PREDEFS ${ARGN})
endfunction()

function(mcc_add_dox)
    set_property(TARGET MCC APPEND PROPERTY MCC_DOXYGEN_INPUTS ${ARGN})
endfunction()

function(mcc_add_test test_target)
    add_executable(${test_target}
        ${ARGN}
    )

    target_link_libraries(${test_target}
        PRIVATE
            MCC::MCC
            GTest::gtest_main
    )

    gtest_discover_tests(${test_target}
        TEST_PREFIX "${test_target}."
        DISCOVERY_MODE PRE_TEST
        PROPERTIES LABELS "MCC"
    )

    set_property(TARGET MCC APPEND PROPERTY MCC_TEST_TARGETS ${test_target})
endfunction()

function(mcc_stage_headers)
    foreach(HEADER ${ARGV})
        file(RELATIVE_PATH REL_HEADER "${MCC_SRC_DIRECTORY}" "${HEADER}")
        get_filename_component(REL_DIR "${REL_HEADER}" DIRECTORY)
        file(MAKE_DIRECTORY "${MCC_BUILD_INCLUDE_DIR}/${REL_DIR}")

        configure_file(
            "${HEADER}"
            "${MCC_BUILD_INCLUDE_DIR}/${REL_HEADER}"
            COPYONLY
        )
    endforeach()
endfunction()
