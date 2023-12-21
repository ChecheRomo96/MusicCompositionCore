#include "../../ScaleFlash.h"

const MCC_MusicalScaleFlash::Container MCC_MusicalScaleFlash::ScaleArrays::Flash[37] =
{
    {&MCC_MusicalScaleFlash::Scales::Chromatic       , NULL},
    {&MCC_MusicalScaleFlash::Scales::Chromatic_Flats , NULL},
    {NULL, &MCC_MusicalScaleFlash::Scales::Major},
    {NULL, &MCC_MusicalScaleFlash::Scales::Ionian},
    {NULL, &MCC_MusicalScaleFlash::Scales::Minor},
    {NULL, &MCC_MusicalScaleFlash::Scales::Aeolian},
    {NULL, &MCC_MusicalScaleFlash::Scales::HarmonicMinor},
    {NULL, &MCC_MusicalScaleFlash::Scales::HarmonicMajor},
    {NULL, &MCC_MusicalScaleFlash::Scales::MajorPentatonic},
    {NULL, &MCC_MusicalScaleFlash::Scales::MinorPentatonic},
    
    {NULL, &MCC_MusicalScaleFlash::Scales::MinorBlues},
    {NULL, &MCC_MusicalScaleFlash::Scales::MajorBlues},
    {NULL, &MCC_MusicalScaleFlash::Scales::Dorian},
    {NULL, &MCC_MusicalScaleFlash::Scales::Phrygian},
    {NULL, &MCC_MusicalScaleFlash::Scales::Lydian},
    {NULL, &MCC_MusicalScaleFlash::Scales::Mixolydian},
    {NULL, &MCC_MusicalScaleFlash::Scales::Locrian},
    {NULL, &MCC_MusicalScaleFlash::Scales::Algerian},
    {NULL, &MCC_MusicalScaleFlash::Scales::Arabic},
    {NULL, &MCC_MusicalScaleFlash::Scales::Augmented},
    
    {NULL, &MCC_MusicalScaleFlash::Scales::Pelog},
    {NULL, &MCC_MusicalScaleFlash::Scales::Byzantine},
    {NULL, &MCC_MusicalScaleFlash::Scales::Chinese},
    {NULL, &MCC_MusicalScaleFlash::Scales::Diminished},
    {NULL, &MCC_MusicalScaleFlash::Scales::Egyptian},
    {NULL, &MCC_MusicalScaleFlash::Scales::EightToneSpanish},
    {NULL, &MCC_MusicalScaleFlash::Scales::Enigmatic},
    {NULL, &MCC_MusicalScaleFlash::Scales::Ethiopian},
    {NULL, &MCC_MusicalScaleFlash::Scales::Hindu},
    {NULL, &MCC_MusicalScaleFlash::Scales::Hirajoshi},
    
    {NULL, &MCC_MusicalScaleFlash::Scales::HungarianMinor},
    {NULL, &MCC_MusicalScaleFlash::Scales::Japanese},
    {NULL, &MCC_MusicalScaleFlash::Scales::Oriental},
    {NULL, &MCC_MusicalScaleFlash::Scales::WholeTone},
    {NULL, &MCC_MusicalScaleFlash::Scales::RomanianMinor},
    {NULL, &MCC_MusicalScaleFlash::Scales::SpanishGypsy},
    {NULL, &MCC_MusicalScaleFlash::Scales::SuperLocrian}
};
