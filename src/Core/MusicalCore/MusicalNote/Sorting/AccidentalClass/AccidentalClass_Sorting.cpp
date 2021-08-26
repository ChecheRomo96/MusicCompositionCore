#include "AccidentalClass_Sorting.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::Ascending(const AccidentalClass& Element, const AccidentalClass& Pivot)
{
    if(Element==Pivot){return Sorting::Equal;}
    else if(Element<Pivot){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 

int8_t Sorting::Descending(const AccidentalClass& Element, const AccidentalClass& Pivot)
{
    if(Element==Pivot){return Sorting::Equal;}
    else if(Element>Pivot){return Sorting::Swap;}
    else{return Sorting::Ignore;}
} 
