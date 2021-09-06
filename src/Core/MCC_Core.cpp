#include "MCC_Core.h"

void MusicCompositionCore::Core::Start()
{
    MCC_MusicalNote::Start();
    //MCC_MidiStart();
}

uint32_t MusicCompositionCore::Core::Micros()
{
    #if defined(ARDUINO)
        return micros();
    #elif defined(PSOC_CREATOR)
        return Timer_ReadCounter();
    #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__APPLE__) || defined(linux)
        return (uint32_t)(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - MusicCompositionCore::StartTime).count());
    #endif

    return 0;
}

