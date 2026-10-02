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

if(MCC_SCALE)
    add_subdirectory(Scale)
endif()

if(MCC_CHORD)
    add_subdirectory(Chord)
endif()

if(MCC_KEY AND MCC_NOTATION AND MCC_CHORD)
    add_subdirectory(Key)
endif()

if(MCC_RHYTHM)
    add_subdirectory(Rhythm)
endif()
