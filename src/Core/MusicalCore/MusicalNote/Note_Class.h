#ifndef MCC_NOTE_CLASS_H
#define MCC_NOTE_CLASS_H

	#include <MCC_BuildSettings.h>
	

  	#include "Pitch/NotePitch.h"
	#include "TextFormat/TextFormat.h"
	#include "Flash/NoteFlash.h"
	//struct MusicCompositionCore::Core::MidiCore::MidiNote;

	namespace MusicCompositionCore::Core::MusicalCore
	{
		#if defined (MCC_MUSICAL_INTERVAL_ENABLED)
	        namespace MusicalInterval
	        {
	            class Interval;
	        }
		#endif

		namespace MusicalNote
		{
			class Note;

			namespace Reference
			{
				extern MusicalNote::Note Note;
				extern float Frequency;
			}

			class Note
			{
				Pitch noteData;
				int8_t octave;

				public:
					///////////////////////////////////////////////////////////////////////
					// Constructors , Destructor and Clear functions
					
						Note();
						
						Note(const Pitch& _pc, int8_t _octave = 3);
                        Note(const Pitch::Letter& _letter, const Pitch::Accidental& _accidental = Pitch::Accidental::Natural, int8_t _octave = 3);

						Note(const Note& source);

						Note& operator=(const Note& source);

						#if defined (MCC_MUSICAL_INTERVAL_ENABLED)
							Note(const Note& source, const MusicalInterval::Interval& interval);
						#endif

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
                		

						#if defined (MCC_MUSICAL_INTERVAL_ENABLED)
	                        Note& operator+=(const MusicalInterval::Interval &rhs);
	                        Note operator+(const MusicalInterval::Interval &rhs) const;
	                
	                        Note& operator-=(const MusicalInterval::Interval &rhs);
	                        Note operator-(const MusicalInterval::Interval &rhs) const;
	                    #endif
                    //
					///////////////////////////////////////////////////////////////////////
					// API

						const char* Name(const TextFormat::FormatClass& format = TextFormat::DefaultFormat)const;
						char* Name(char* buff, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);

						const int16_t NotePitch() const;
						const uint8_t MidiPitch() const;

						const float Frequency( const Note& ReferenceNote = Reference::Note, float ReferenceFrequeny = Reference::Frequency ) const;

						///////////////////////////////////////////////////////////////////////
						// Octaves

							void SetOctave(int8_t octave);
							void OctaveUp();
							void OctaveDown();
                            const int8_t Octave() const;
                        //
                        ///////////////////////////////////////////////////////////////////////
                        // Pitch
							
							void SetPitch(const Pitch& src);
							const Pitch& GetPitch() const;
							
							///////////////////////////////////////////////////////////////
							// Accidental
								
								void SetAccidental(const Pitch::Accidental& src);
								const Pitch::Accidental& Accidental() const;

								bool Flat();
								bool Sharp();
							//
							///////////////////////////////////////////////////////////////
							// Letter

								void SetLetter(const Pitch::Letter& src);
                            	const Pitch::Letter& Letter() const;

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
            
			static constexpr int16_t InvalidPitch = INT16_MAX;
			
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

			// Reference Note for computing Frequency

            void SetReferenceNote(const Note& Note, const float& Frequency);
            void SetReferenceNote(const Pitch::Letter::LetterType& Letter, const Pitch::Accidental::AccidentalType& Accidental, int8_t Octave, const float& Frequency);
		}
	}
		
#endif//MCC_NOTE_CLASS_H
