#ifndef MCC_MUSICAL_INTERVAL_FLASH_H
#define MCC_MUSICAL_INTERVAL_FLASH_H

    #include <MCC_BuildSettings.h>

    #include "../MusicalInterval_Definitions.h"

    namespace MusicCompositionCore
    {
      namespace Core
        {
          namespace MusicalCore
            {
                namespace MusicalInterval
                {
                    static constexpr uint8_t InvalidInterval = 0xFF;

                    namespace Flash
                    {
                        uint8_t GetIntervalSemitones(uint8_t IntervalType, uint8_t IntervalQuality);
                        
                        const char* GetGenericIntervalStr(uint8_t IntervalType);
                        char* GetGenericIntervalStr(char* buff, uint8_t IntervalType);

                        const char* GetIntervalQualityStr(uint8_t IntervalQuality);
                        char* GetIntervalQualityStr(char* buff, uint8_t IntervalQuality);

                        const char* GetIntervalName(uint8_t IntervalType, uint8_t IntervalQuality);
                        char* GetIntervalName(char* buff, uint8_t IntervalType, uint8_t IntervalQuality);

                        const uint8_t IntervalMap[7][3] PROGMEM_MACRO
                        {           
                            { InvalidInterval,                          0, InvalidInterval},
                            {                          1, InvalidInterval,                          2},
                            {                          3, InvalidInterval,                          4},
                            { InvalidInterval,                          5, InvalidInterval},
                            { InvalidInterval,                          7, InvalidInterval},
                            {                          8, InvalidInterval,                          9},
                            {                         10, InvalidInterval,                         11}
                        };

                        const char PrimeStr[] PROGMEM_MACRO = {'P','r','i','m','e','\0'};
                        const char SecondStr[] PROGMEM_MACRO = {'S','e','c','o','n','d','\0'};
                        const char ThirdStr[] PROGMEM_MACRO = {'T','h','i','r','d','\0'};
                        const char FourthStr[] PROGMEM_MACRO = {'F','o','u','r','t','h','\0'};
                        const char FifthStr[] PROGMEM_MACRO = {'F','i','f','t','h','\0'};
                        const char SixthStr[] PROGMEM_MACRO = {'S','i','x','t','h','\0'};
                        const char SeventhStr[] PROGMEM_MACRO = {'S','e','v','e','n','t','h','\0'};
                        const char OctaveStr[] PROGMEM_MACRO = {'O','c','t','a','v','e','\0'};
                        const char NinthStr[] PROGMEM_MACRO = {'N','i','n','t','h','\0'};
                        const char TenthStr[] PROGMEM_MACRO = {'T','e','n','t','h','\0'};
                        const char EleventhSrt[] PROGMEM_MACRO = {'E','l','e','v','e','n','t','h','\0'};
                        const char TwelvethStr[] PROGMEM_MACRO = {'T','w','e','l','v','e','t','h','\0'};
                        const char ThirteenthStr[] PROGMEM_MACRO = {'T','h','i','r','t','e','e','n','t','h','\0'};
                        const char FourteenthStr[] PROGMEM_MACRO = {'F','o','u','r','t','e','e','n','t','h','\0'};
                        const char CompoundStr[] PROGMEM_MACRO = {'C','o','m','p','o','u','n','d','\0'};

                        const char* const GenericIntervalNames[15] PROGMEM_MACRO = 
                        {
                            PrimeStr,
                            SecondStr,
                            ThirdStr,
                            FourthStr,
                            FifthStr,
                            SixthStr,
                            SeventhStr,
                            OctaveStr,
                            NinthStr,
                            TenthStr,
                            EleventhSrt,
                            TwelvethStr,
                            ThirteenthStr,
                            FourteenthStr,
                            CompoundStr
                        };

                        const char QuadruplyDiminishedStr[] PROGMEM_MACRO = {'Q','u','a','d','r','u','p','l','y',' ','D','i','m','i','n','i','s','h','e','d','\0'};
                        const char TriplyDiminishedStr[] PROGMEM_MACRO = {'T','r','i','p','l','y',' ','D','i','m','i','n','i','s','h','e','d','\0'};
                        const char DoublyDiminishedStr[] PROGMEM_MACRO = {'D','o','u','b','l','y',' ','D','i','m','i','n','i','s','h','e','d','\0'};
                        const char DiminishedStr[] PROGMEM_MACRO = {'D','i','m','i','n','i','s','h','e','d','\0'};
                        const char MinorStr[] PROGMEM_MACRO = {'M','i','n','o','r','\0'};
                        const char PerfectStr[] PROGMEM_MACRO = {'P','e','r','f','e','c','t','\0'};
                        const char MajorStr[] PROGMEM_MACRO = {'M','a','j','o','r','\0'};
                        const char AugmentedStr[] PROGMEM_MACRO = {'A','u','g','m','e','n','t','e','d','\0'};
                        const char DoublyAugmentedStr[] PROGMEM_MACRO = {'D','o','u','b','l','y',' ','A','u','g','m','e','n','t','e','d','\0'};
                        const char TriplyAugmentedStr[] PROGMEM_MACRO = {'T','r','i','p','l','y',' ','A','u','g','m','e','n','t','e','d','\0'};
                        const char QuadruplyAugmentedStr[] PROGMEM_MACRO = {'Q','u','a','d','r','u','p','l','y',' ','A','u','g','m','e','n','t','e','d','\0'};

                        const char* const IntervalQualitiesNames[11] PROGMEM_MACRO = 
                        {
                            QuadruplyDiminishedStr,
                            TriplyDiminishedStr,
                            DoublyDiminishedStr,
                            DiminishedStr,
                            MinorStr,
                            PerfectStr,
                            MajorStr,
                            AugmentedStr,
                            DoublyAugmentedStr,
                            TriplyAugmentedStr,
                            QuadruplyAugmentedStr
                        };
                        extern char buffer[41];
                    }
                }
            }
        }
    }



#endif//MCC_MUSICAL_INTERVAL_FLASH_H
