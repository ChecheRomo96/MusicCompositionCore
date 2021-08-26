#include "PitchClass_Sorting.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::Letter_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.Letter()==Pivot.Letter()){return Sorting::Equal;}
    else if(Element.Letter()<Pivot.Letter()){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 

int8_t Sorting::Letter_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.Letter()==Pivot.Letter()){return Sorting::Equal;}
    else if(Element.Letter()>Pivot.Letter()){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 

int8_t Sorting::Accidental_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.Accidental()==Pivot.Accidental()){return Sorting::Equal;}
    else if(Element.Accidental()<Pivot.Accidental()){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 

int8_t Sorting::Accidental_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.Accidental()==Pivot.Accidental()){return Sorting::Equal;}
    else if(Element.Accidental()>Pivot.Accidental()){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 

int8_t Sorting::NotePitch_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return Sorting::Equal;}
    else if(Element.NotePitch()<Pivot.NotePitch()){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 

int8_t Sorting::NotePitch_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.NotePitch()==Pivot.NotePitch()){return Sorting::Equal;}
    else if(Element.NotePitch()>Pivot.NotePitch()){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 

int8_t Sorting::MidiPitch_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return Sorting::Equal;}
    else if(Element.MidiPitch()<Pivot.MidiPitch()){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 

int8_t Sorting::MidiPitch_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot)
{
    if(Element.MidiPitch()==Pivot.MidiPitch()){return Sorting::Equal;}
    else if(Element.MidiPitch()>Pivot.MidiPitch()){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 