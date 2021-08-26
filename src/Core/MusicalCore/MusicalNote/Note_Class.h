#ifndef MCC_NOTE_CLASS_H
#define MCC_NOTE_CLASS_H

	#include <MCC_BuildSettings.h>
	

  	#include "Pitch/NotePitch.h"
	#include "Format/NoteFormat.h"
	#include "Flash/NoteFlash.h"
	//struct MusicCompositionCore::Core::MidiCore::MidiNote;

	namespace MusicCompositionCore
	{
        namespace Core
        {
        	namespace MusicalCore
       		{
                namespace MusicalInterval
                {
                    class Interval;
                }
                
       			namespace MusicalNote
       			{
                 
					class Note
					{
						Pitch::PitchClass noteData;
						int8_t octave;

						public:
							///////////////////////////////////////////////////////////////////////
							// Constructors , Destructor and Clear functions
							
								Note();
								
								Note(const Pitch::PitchClass& _pc, int8_t _octave = 3);
                                Note(const Pitch::Letter::LetterClass& _letter, const Pitch::Accidental::AccidentalClass& _accidental = Pitch::Accidental::Natural, int8_t _octave = 3);

								Note(const Note& source);
								Note& operator=(const Note& source);

								Note(const Note& source, const MusicalInterval::Interval& interval);
								//Note(const MidiNote& source);
							//
							///////////////////////////////////////////////////////////////////////
							// Operators

								friend bool operator < (const Note& lhs, const Note& rhs);
								friend bool operator <= (const Note& lhs, const Note& rhs);
								friend bool operator > (const Note& lhs, const Note& rhs);
								friend bool operator >= (const Note& lhs, const Note& rhs);
								friend bool operator == (const Note& lhs, const Note& rhs);
								friend bool operator != (const Note& lhs, const Note& rhs);
                        
                                Note& operator+=(const MusicalInterval::Interval &rhs);
                                Note operator+(const MusicalInterval::Interval &rhs) const;
                        
                                Note& operator-=(const MusicalInterval::Interval &rhs);
                                Note operator-(const MusicalInterval::Interval &rhs) const;
                            //
							///////////////////////////////////////////////////////////////////////
							// API

								const char* Name(const NoteFormat::Format& format = NoteFormat::DefaultFormat)const;
								char* Name(char* buff, const NoteFormat::Format& format = NoteFormat::DefaultFormat);

								const int16_t NotePitch() const;
								const uint8_t MidiPitch() const;

								///////////////////////////////////////////////////////////////////////
								// Octaves

									void SetOctave(int8_t octave);
									void OctaveUp();
									void OctaveDown();
	                                const int8_t Octave() const;
	                            //
	                            ///////////////////////////////////////////////////////////////////////
	                            // Pitch
									
									void SetPitch(const Pitch::PitchClass& src);
									const Pitch::PitchClass& Pitch() const;
									
									///////////////////////////////////////////////////////////////
									// Accidental
										
										void SetAccidental(const Pitch::Accidental::AccidentalClass& src);
										const Pitch::Accidental::AccidentalClass& Accidental() const;

										bool Flat();
										bool Sharp();
									//
									///////////////////////////////////////////////////////////////
									// Letter

										void SetLetter(const Pitch::Letter::LetterClass& src);
	                                	const Pitch::Letter::LetterClass& Letter() const;

										void Next();
										void Previous();
									//
									///////////////////////////////////////////////////////////////
								//
								///////////////////////////////////////////////////////////////////
							//
							///////////////////////////////////////////////////////////////////////
					}; 

					extern Note NoteBuffer;
                    extern const Note InvalidNote;
                    
					static constexpr int16_t InvalidNotePitch = INT16_MAX;
					
					bool operator < (const Note& lhs, const Note& rhs);
					bool operator <= (const Note& lhs, const Note& rhs);
					bool operator > (const Note& lhs, const Note& rhs);
					bool operator >= (const Note& lhs, const Note& rhs);
					bool operator == (const Note& lhs, const Note& rhs);
					bool operator != (const Note& lhs, const Note& rhs);


					// Compare Mode is for checking for equalities and inequalities

       				namespace CompareMode 
       				{
       					extern bool CurrentMode;
       					static constexpr bool Name = 0;
       					static constexpr bool Pitch = 1;
       				}

       				void CompareNames();
       				void ComparePitches();
       				void SetCompareMode(bool newMode);
				}
			}
		}
	}

	
#endif//MCC_NOTE_CLASS_H
