#include "NoteClass_Sorting.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::Ascending(const LetterClass& Element, const LetterClass& Pivot)
{
    if(Element==Pivot){return Sorting::Equal;}
    else if(Element<Pivot){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 

int8_t Sorting::Descending(const LetterClass& Element, const LetterClass& Pivot)
{
    if(Element==Pivot){return Sorting::Equal;}
    else if(Element>Pivot){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 
