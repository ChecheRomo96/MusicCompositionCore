#include "PitchClass_Sorting.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::PitchClass::Letter_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.Letter()==Pivot.Letter()){return CPVector::Sorting::Equal;}
    else if(Element.Letter()<Pivot.Letter()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::Letter_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.Letter()==Pivot.Letter()){return CPVector::Sorting::Equal;}
    else if(Element.Letter()>Pivot.Letter()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::Accidental_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.Accidental()==Pivot.Accidental()){return CPVector::Sorting::Equal;}
    else if(Element.Accidental()<Pivot.Accidental()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::Accidental_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.Accidental()==Pivot.Accidental()){return CPVector::Sorting::Equal;}
    else if(Element.Accidental()>Pivot.Accidental()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::NotePitch_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return CPVector::Sorting::Equal;}
    else if(Element.NotePitch()<Pivot.NotePitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::NotePitch_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return CPVector::Sorting::Equal;}
    else if(Element.NotePitch()>Pivot.NotePitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::MidiPitch_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return CPVector::Sorting::Equal;}
    else if(Element.MidiPitch()<Pivot.MidiPitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::MidiPitch_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return CPVector::Sorting::Equal;}
    else if(Element.MidiPitch()>Pivot.MidiPitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 
