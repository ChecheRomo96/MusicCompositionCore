#include "LetterSorting.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::Letter::Ascending(const Pitch::Letter& Element, const Pitch::Letter& Pivot)
{
    if(Element==Pivot){return CPVector::Sorting::Equal;}
    else if(Element<Pivot){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::Letter::Descending(const Pitch::Letter& Element, const Pitch::Letter& Pivot)
{
    if(Element==Pivot){return CPVector::Sorting::Equal;}
    else if(Element>Pivot){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 
