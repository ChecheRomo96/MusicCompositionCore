#ifndef MCC_MUSICAL_NOTE_H
#define MCC_MUSICAL_NOTE_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore::MusicalNote
	{
		void Start();
	}

	namespace MCC_MusicalNote = MusicCompositionCore::MusicalNote;

	#include "Flash/NoteFlash.h"
	#include "TextFormat/TextFormat.h"
	#include "Pitch/NotePitch.h"
	#include "Sorting/MusicalNote_Sorting.h"
	
	#include "Note_Class.h"

#endif//MCC_MUSICAL_NOTE_H
