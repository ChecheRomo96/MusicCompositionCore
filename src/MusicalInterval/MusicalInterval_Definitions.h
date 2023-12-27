#ifndef MCC_MUSICAL_INTERVAL_DEFINITIONS_H
#define MCC_MUSICAL_INTERVAL_DEFINITIONS_H

    namespace MusicCompositionCore
    {
        namespace MusicalInterval
        {
            typedef uint8_t NumberType;
            typedef uint8_t QualityType;

            namespace Numbers
            {
                static constexpr NumberType Prime = 0u;
                static constexpr NumberType Second = 1u;
                static constexpr NumberType Third = 2u;
                static constexpr NumberType Fourth = 3u;
                static constexpr NumberType Fifth = 4u;
                static constexpr NumberType Sixth = 5u;
                static constexpr NumberType Seventh = 6u;
                static constexpr NumberType Octave = 7u;
                static constexpr NumberType Ninth = 8u;
                static constexpr NumberType Tenth = 9u;
                static constexpr NumberType Eleventh = 10u;
                static constexpr NumberType Twelveth = 11u;
                static constexpr NumberType Thirteenth = 12u;
                static constexpr NumberType Fourteenth = 13u;
                static constexpr NumberType InvalidNumber = 0xFF;
                static constexpr uint8_t Count = 14u;
            }

            namespace Qualities
            {
                static constexpr QualityType QuadruplyDiminished = 0u;
                static constexpr QualityType TriplyDiminished = 1u;
                static constexpr QualityType DoublyDiminished = 2u;
                static constexpr QualityType Diminished = 3u;
                static constexpr QualityType Minor = 4u;
                static constexpr QualityType Perfect = 5u;
                static constexpr QualityType Major = 6u;
                static constexpr QualityType Augmented = 7u;
                static constexpr QualityType DoublyAugmented = 8u;
                static constexpr QualityType TriplyAugmented = 9u;
                static constexpr QualityType QuadruplyAugmented = 10u;
                static constexpr QualityType InvalidQuality = 11u;
                static constexpr uint8_t Count = 11u;
            }
        }
    }

    namespace MCC_MusicalInterval = MusicCompositionCore::MusicalInterval;

#endif//MCC_MUSICAL_INTERVAL_DEFINITIONS_H