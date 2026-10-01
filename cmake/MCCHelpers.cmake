function(mcc_add_macro visibility)
    target_compile_definitions(MCC ${visibility} ${ARGN})
    set_property(TARGET MCC APPEND PROPERTY MCC_DOXYGEN_PREDEFS ${ARGN})
endfunction()

function(mcc_add_dox)
    set_property(TARGET MCC APPEND PROPERTY MCC_DOXYGEN_INPUTS ${ARGN})
endfunction()

# Agreed warning set for MCC's own targets when testing, matching
# Foundation. Warnings are errors; pass --compile-no-warning-as-error to cmake
# to relax locally.
function(mcc_enable_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion
            -Wold-style-cast -Wnon-virtual-dtor -Woverloaded-virtual
        )
    endif()
    set_target_properties(${target} PROPERTIES COMPILE_WARNING_AS_ERROR ON)
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

    # Test sources spell Unicode accidentals as escapes in narrow literals,
    # which need a UTF-8 execution character set on MSVC.
    target_compile_options(${test_target} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
    mcc_enable_warnings(${test_target})

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
