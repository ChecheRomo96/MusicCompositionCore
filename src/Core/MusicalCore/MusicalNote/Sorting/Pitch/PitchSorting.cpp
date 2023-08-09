#include "PitchSorting.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::Pitch::Letter_Ascending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot)
{
    if(Element.GetLetter()==Pivot.GetLetter()){return CPVector::Sorting::Equal;}
    else if(Element.GetLetter()<Pivot.GetLetter()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Pitch::Letter_Descending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot)
{
    if(Element.GetLetter()==Pivot.GetLetter()){return CPVector::Sorting::Equal;}
    else if(Element.GetLetter()>Pivot.GetLetter()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Pitch::Accidental_Ascending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot)
{
    if(Element.GetAccidental()==Pivot.GetAccidental()){return CPVector::Sorting::Equal;}
    else if(Element.GetAccidental()<Pivot.GetAccidental()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Pitch::Accidental_Descending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot)
{
    if(Element.GetAccidental()==Pivot.GetAccidental()){return CPVector::Sorting::Equal;}
    else if(Element.GetAccidental()>Pivot.GetAccidental()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Pitch::NotePitch_Ascending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return CPVector::Sorting::Equal;}
    else if(Element.NotePitch()<Pivot.NotePitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Pitch::NotePitch_Descending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return CPVector::Sorting::Equal;}
    else if(Element.NotePitch()>Pivot.NotePitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Pitch::MidiPitch_Ascending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return CPVector::Sorting::Equal;}
    else if(Element.MidiPitch()<Pivot.MidiPitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Pitch::MidiPitch_Descending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return CPVector::Sorting::Equal;}
    else if(Element.MidiPitch()>Pivot.MidiPitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 
