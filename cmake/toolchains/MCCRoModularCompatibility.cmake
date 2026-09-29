# Temporary compatibility adapter for the RoModularBuild migration.
# MCC keeps its public cache variables while the shared implementation uses
# project-independent ROMODULAR_* names.

function(mcc_forward_toolchain_cache
    MCC_NAME
    ROMODULAR_NAME
    CACHE_TYPE
    DEFAULT_VALUE
    DESCRIPTION
)
    if(NOT DEFINED ${MCC_NAME})
        if(DEFINED ${ROMODULAR_NAME})
            set(${MCC_NAME} "${${ROMODULAR_NAME}}" CACHE ${CACHE_TYPE}
                "${DESCRIPTION}")
        else()
            set(${MCC_NAME} "${DEFAULT_VALUE}" CACHE ${CACHE_TYPE}
                "${DESCRIPTION}")
        endif()
    endif()

    if(DEFINED ${ROMODULAR_NAME} AND
       NOT "${${ROMODULAR_NAME}}" STREQUAL "${${MCC_NAME}}")
        message(WARNING
            "Both ${MCC_NAME} and ${ROMODULAR_NAME} are set; "
            "MCC compatibility gives ${MCC_NAME} precedence"
        )
    endif()

    set(${ROMODULAR_NAME} "${${MCC_NAME}}" CACHE ${CACHE_TYPE}
        "${DESCRIPTION}" FORCE)
endfunction()
