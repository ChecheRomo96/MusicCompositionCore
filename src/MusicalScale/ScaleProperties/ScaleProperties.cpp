#include "ScaleProperties.h"

MusicCompositionCore::MusicalScale::PropertiesContainer::PropertiesContainer(bool note_mode, uint8_t scale_location, bool name_flag)
{
    Data =
    (note_mode<<ScaleProperties::MappingMode::bitshift)|
    ((scale_location&0b11)<<ScaleProperties::Location::bitshift)|
    (name_flag<<ScaleProperties::NameFlag::bitshift);
}

MusicCompositionCore::MusicalScale::PropertiesContainer::PropertiesContainer(uint8_t bitmap)
{
    Data = bitmap;
}

MusicCompositionCore::MusicalScale::PropertiesContainer::PropertiesContainer(const PropertiesContainer& source)
{
    SetMappingMode(source.MappingMode());
    SetLocation(source.Location());
    SetNameFlag(source.NameFlag());
}

const bool MusicCompositionCore::MusicalScale::PropertiesContainer::MappingMode() const
{
    return (Data>> ScaleProperties::MappingMode::bitshift )&1u;
}

void MusicCompositionCore::MusicalScale::PropertiesContainer::SetMappingMode(bool noteMode)
{
    Data &= ~(1u<<ScaleProperties::MappingMode::bitshift);
    Data |= ((uint8_t)noteMode<<ScaleProperties::MappingMode::bitshift);
}
const uint8_t MusicCompositionCore::MusicalScale::PropertiesContainer::Location() const
{
    return (Data>>ScaleProperties::Location::bitshift)&0b11;
}

void MusicCompositionCore::MusicalScale::PropertiesContainer::SetLocation(uint8_t scale_location)
{
    Data &= ~(0b11<<ScaleProperties::Location::bitshift);
    Data |= ((uint8_t)(scale_location&0b11)<<ScaleProperties::Location::bitshift);
}

const bool MusicCompositionCore::MusicalScale::PropertiesContainer::NameFlag() const
{
    return (Data>>ScaleProperties::NameFlag::bitshift)&1u;
}

void MusicCompositionCore::MusicalScale::PropertiesContainer::SetNameFlag(bool flag)
{
    Data &= ~(1u<<ScaleProperties::NameFlag::bitshift);
    Data |= ((uint8_t)flag<<ScaleProperties::NameFlag::bitshift);
}
