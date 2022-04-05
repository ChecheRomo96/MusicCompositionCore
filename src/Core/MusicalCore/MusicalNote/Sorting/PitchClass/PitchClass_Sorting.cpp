#include "PitchClass_Sorting.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::PitchClass::Letter_Ascending(const Pitch& Element, const Pitch& Pivot)
{
    if(Element.GetLetter()==Pivot.GetLetter()){return CPVector::Sorting::Equal;}
    else if(Element.GetLetter()<Pivot.GetLetter()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::Letter_Descending(const Pitch& Element, const Pitch& Pivot)
{
    if(Element.GetLetter()==Pivot.GetLetter()){return CPVector::Sorting::Equal;}
    else if(Element.GetLetter()>Pivot.GetLetter()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::Accidental_Ascending(const Pitch& Element, const Pitch& Pivot)
{
    if(Element.GetAccidental()==Pivot.GetAccidental()){return CPVector::Sorting::Equal;}
    else if(Element.GetAccidental()<Pivot.GetAccidental()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::Accidental_Descending(const Pitch& Element, const Pitch& Pivot)
{
    if(Element.GetAccidental()==Pivot.GetAccidental()){return CPVector::Sorting::Equal;}
    else if(Element.GetAccidental()>Pivot.GetAccidental()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::NotePitch_Ascending(const Pitch& Element, const Pitch& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return CPVector::Sorting::Equal;}
    else if(Element.NotePitch()<Pivot.NotePitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::NotePitch_Descending(const Pitch& Element, const Pitch& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return CPVector::Sorting::Equal;}
    else if(Element.NotePitch()>Pivot.NotePitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::MidiPitch_Ascending(const Pitch& Element, const Pitch& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return CPVector::Sorting::Equal;}
    else if(Element.MidiPitch()<Pivot.MidiPitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::PitchClass::MidiPitch_Descending(const Pitch& Element, const Pitch& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return CPVector::Sorting::Equal;}
    else if(Element.MidiPitch()>Pivot.MidiPitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 
