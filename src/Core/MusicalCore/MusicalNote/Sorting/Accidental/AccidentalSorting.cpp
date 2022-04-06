#include "AccidentalSorting.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::Accidental::Ascending(const Pitch::Accidental& Element, const Pitch::Accidental& Pivot)
{
    if(Element==Pivot){return CPVector::Sorting::Equal;}
    else if(Element<Pivot){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Accidental::Descending(const Pitch::Accidental& Element, const Pitch::Accidental& Pivot)
{
    if(Element==Pivot){return CPVector::Sorting::Equal;}
    else if(Element>Pivot){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 
