#ifndef MCC_MUSICAL_SCALE_DEFINITIONS_H
#define MCC_MUSICAL_SCALE_DEFINITIONS_H

    #include <MCC_BuildSettings.h>

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

        #include "..\MusicalNote\MusicalNote.h"

        #ifdef _WIN64
          //define something for Windows (64-bit only)
        #else
          //define something for Windows (32-bit only)
        #endif

    #elif __APPLE__

        #include <TargetConditionals.h>

        #include "../MusicalNote/MusicalNote.h"

        #if TARGET_IPHONE_SIMULATOR
             // iOS Simulator
        #elif TARGET_OS_IPHONE
            // iOS device
        #elif TARGET_OS_MAC
            // Other kinds of Mac OS
        #else
        #   error "Unknown Apple platform"
        #endif

    #elif ARDUINO

        #include "../MusicalNote/MusicalNote.h"

    #elif __linux__
        // linux
    #elif __unix__ // all unices not caught above
        // Unix
    #elif defined(_POSIX_VERSION)
        // POSIX
    #else
    #   error "Unknown compiler"
    #endif

    namespace MusicCompositionCore
    {
        namespace MusicalCore
        {
            namespace MusicalScale
            {
                namespace Constants
                {
                    
                    /*static constexpr uint8_t ScaleRootsSize = 17;
                    const MCC_MusicalNote::NoteToken ScaleRoots[ScaleRootsSize]  PROGMEM_MACRO=
                    {
                        MCC_MusicalNote::Constants::NoteToken::C_Natural,
                        MCC_MusicalNote::Constants::NoteToken::C_Sharp,
                        MCC_MusicalNote::Constants::NoteToken::D_Flat,
                        MCC_MusicalNote::Constants::NoteToken::D_Natural,
                        MCC_MusicalNote::Constants::NoteToken::D_Sharp,
                        MCC_MusicalNote::Constants::NoteToken::E_Flat,
                        MCC_MusicalNote::Constants::NoteToken::E_Natural,
                        MCC_MusicalNote::Constants::NoteToken::F_Natural,
                        MCC_MusicalNote::Constants::NoteToken::F_Sharp,
                        MCC_MusicalNote::Constants::NoteToken::G_Flat,
                        MCC_MusicalNote::Constants::NoteToken::G_Natural,
                        MCC_MusicalNote::Constants::NoteToken::G_Sharp,
                        MCC_MusicalNote::Constants::NoteToken::A_Flat,
                        MCC_MusicalNote::Constants::NoteToken::A_Natural,
                        MCC_MusicalNote::Constants::NoteToken::A_Sharp,
                        MCC_MusicalNote::Constants::NoteToken::B_Flat,
                        MCC_MusicalNote::Constants::NoteToken::B_Natural,
                    };*/
                }
            }
        }
    }
    
    namespace MCC_MusicalScaleConstants = MusicCompositionCore::MusicalCore::MusicalScale::Constants;

#endif//MCC_MUSICAL_SCALE_DEFINITIONS_H
