#include "NoteClass_Sorting.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::Note::Letter_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.Letter()==Pivot.Letter()){return CPVector::Sorting::Equal;}
    else if(Element.Letter()<Pivot.Letter()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Note::Letter_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.Letter()==Pivot.Letter()){return CPVector::Sorting::Equal;}
    else if(Element.Letter()>Pivot.Letter()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Note::Accidental_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.Accidental()==Pivot.Accidental()){return CPVector::Sorting::Equal;}
    else if(Element.Accidental()<Pivot.Accidental()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Note::Accidental_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.Accidental()==Pivot.Accidental()){return CPVector::Sorting::Equal;}
    else if(Element.Accidental()>Pivot.Accidental()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Note::Octave_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.Octave()==Pivot.Octave()){return CPVector::Sorting::Equal;}
    else if(Element.Octave()<Pivot.Octave()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Note::Octave_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.Octave()==Pivot.Octave()){return CPVector::Sorting::Equal;}
    else if(Element.Octave()>Pivot.Octave()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Note::NotePitch_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return CPVector::Sorting::Equal;}
    else if(Element.NotePitch()<Pivot.NotePitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Note::NotePitch_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return CPVector::Sorting::Equal;}
    else if(Element.NotePitch()>Pivot.NotePitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Note::MidiPitch_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return CPVector::Sorting::Equal;}
    else if(Element.MidiPitch()<Pivot.MidiPitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Note::MidiPitch_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return CPVector::Sorting::Equal;}
    else if(Element.MidiPitch()>Pivot.MidiPitch()){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 
