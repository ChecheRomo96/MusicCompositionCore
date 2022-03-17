#include <CPVector.h>
#include "AccidentalClass_Sorting.h"


using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

int8_t Sorting::AccidentalClass::Ascending(const Pitch::Accidental::AccidentalClass& Element, const Pitch::Accidental::AccidentalClass& Pivot)
{
    if(Element==Pivot){return CPVector::Sorting::Equal;}
    else if(Element<Pivot){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 

int8_t Sorting::AccidentalClass::Descending(const Pitch::Accidental::AccidentalClass& Element, const Pitch::Accidental::AccidentalClass& Pivot)
{
    if(Element==Pivot){return CPVector::Sorting::Equal;}
    else if(Element>Pivot){return CPVector::Sorting::Swap;}
    else{return CPVector::Sorting::Ignore;}
} 
