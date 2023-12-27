#ifndef MCC_SCALE_PROPERTIES_CLASS_H
#define MCC_SCALE_PROPERTIES_CLASS_H

    #include <MCC_BuildSettings.h>

    namespace MusicCompositionCore
    {
            namespace MusicalScale
            {
                class PropertiesContainer{
                protected:
                    uint8_t Data;

                public:

                    PropertiesContainer(bool note_mode, uint8_t scale_location, bool name_flag);
                    PropertiesContainer(uint8_t bitmap);
                    PropertiesContainer(const PropertiesContainer& source);

                    const bool MappingMode() const;
                    void SetMappingMode(bool note_mode);
                    
                    const uint8_t Location() const; 
                    void SetLocation(uint8_t scale_location);
                    
                    const bool NameFlag() const; 
                    void SetNameFlag(bool name_flag);
                };
            }
    }



#endif//MCC_SCALE_PROPERTIES_CLASS_H
