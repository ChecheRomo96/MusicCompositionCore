#include "MusicalNote.h"

#include "../MusicalInterval/MusicalInterval.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////
// Note Buffer

    MCC_MusicalNote::Note MCC_MusicalNote::NoteBuffer;
    const MCC_MusicalNote::Note MCC_MusicalNote::InvalidNote;
//
/////////////////////////////////////////////////////////////////////////
// Compare Mode

    void MCC_MusicalNote::Start()
    {
    	MCC_MusicalNote::NoteBuffer.SetLetter(MCC_MusicalNote::Pitch::Letter::A);
    	MCC_MusicalNote::NoteBuffer.SetAccidental(MCC_MusicalNote::Pitch::Accidental::Natural);
    	MCC_MusicalNote::NoteBuffer.SetOctave(4);

    	MCC_MusicalNote::SetReferenceNote(MCC_MusicalNote::NoteBuffer,440.0);
    }
//
/////////////////////////////////////////////////////////////////////////
// Compare Mode

        bool MCC_MusicalNote::CompareMode::CurrentMode = MCC_MusicalNote::CompareMode::Name;

		void MCC_MusicalNote::CompareNames()
		{
		    CompareMode::CurrentMode =  CompareMode::Name;
		}   

		void MCC_MusicalNote::ComparePitches()
		{
		    CompareMode::CurrentMode =  CompareMode::Pitch;
		}

		void MCC_MusicalNote::SetCompareMode(bool newMode)
		{  
		    if(newMode == CompareMode::Pitch)
		    {
		        ComparePitches();
		    }
		    else
		    {
		        CompareNames();
		    }
		}
//
/////////////////////////////////////////////////////////////////////////
// Reference Mode

        MCC_MusicalNote::Note MCC_MusicalNote::Reference::Note(MCC_MusicalNote::Pitch::A_Natural, 4);
        float MCC_MusicalNote::Reference::Frequency = 440;

        void MCC_MusicalNote::SetReferenceNote(const Note& Note, const float& Frequency)
        {
        	Reference::Note = Note;
        	Reference::Frequency = Frequency;
        }

        void MCC_MusicalNote::SetReferenceNote(const Pitch::Letter::LetterType& Letter, const Pitch::Accidental::AccidentalType& Accidental, int8_t Octave, const float& Frequency)
        {
        	Reference::Note = Note(Letter,Accidental, Octave);
        	Reference::Frequency = Frequency;
        }
//
/////////////////////////////////////////////////////////////////////////
// Note Class

		using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

		///////////////////////////////////////////////////////////////////////
		// Constructors , Destructor and Clear functions

			Note::Note()
			{
				noteData = Pitch::InvaildPitch;
			    octave = 0;
			}

			Note::Note(const Pitch::Letter& Letter, const Pitch::Accidental& Accidental, int8_t Octave)
			{
			    noteData.SetLetter(Letter);
			    noteData.SetAccidental(Accidental);
			    SetOctave(Octave);
			}

			Note::Note(const MusicalNote::Pitch& Source, int8_t Octave)
			{
			    noteData = Source;
			    SetOctave(Octave);
			}

			Note::Note(const Note& Source)
			{
			    noteData = Source.GetPitch();
			    SetOctave(Source.Octave());
			}

			Note& Note::operator=(const Note& Source)
			{
			    noteData = Source.GetPitch();
			    SetOctave(Source.Octave());
			    return (*this);
			}

			#if defined (MCC_MUSICAL_INTERVAL_ENABLED)
				Note::Note(const Note& Source, const MCC_MusicalInterval::Interval& interval)
				{
				    noteData = Source.GetPitch();
				    SetOctave(Source.Octave());
				    (*this)+=interval;
				}
			#endif

		//
		///////////////////////////////////////////////////////////////////////
		// Operators

			bool MCC_MusicalNote::operator < (const Note &lhs, const Note &rhs)
			{
			    if(MCC_MusicalNote::CompareMode::CurrentMode == MCC_MusicalNote::CompareMode::Name)
			    {
			        if(lhs.Letter().ID() < rhs.Letter().ID())
			        {
			        	return 1;
			        }
			        else if(lhs.Letter().ID() == rhs.Letter().ID())
			        {
			        	if(lhs.Accidental().ID() < rhs.Accidental().ID())
			        	{
			            	return 1;
			        	}
			        }
			    	return 0;
			    }
			    else
			    {
			        if(lhs.NotePitch() < rhs.NotePitch())
			        {
			            return 1;
			        }
			    }
			    return 0;
			}

			bool MCC_MusicalNote::operator <= (const Note &lhs, const Note &rhs)
			{
			    if(MCC_MusicalNote::CompareMode::CurrentMode == MCC_MusicalNote::CompareMode::Name)
			    {
			        if(lhs.Letter().ID() < rhs.Letter().ID())
			        {
			        	return 1;
			        }
			        else if(lhs.Letter().ID() == rhs.Letter().ID())
			        {
			        	if(lhs.Accidental().ID() <= rhs.Accidental().ID())
			        	{
			            	return 1;
			        	}
			        }
			    	return 0;
			    }
			    else
			    {
			        if(lhs.NotePitch() <= rhs.NotePitch())
			        {
			            return 1;
			        }
			    }
			    return 0;
			}

			bool MCC_MusicalNote::operator > (const Note &lhs, const Note &rhs)
			{
			    if(MCC_MusicalNote::CompareMode::CurrentMode == MCC_MusicalNote::CompareMode::Name)
			    {
			        if(lhs.Letter().ID() > rhs.Letter().ID())
			        {
			        	return 1;
			        }
			        else if(lhs.Letter().ID() == rhs.Letter().ID())
			        {
			        	if(lhs.Accidental().ID() > rhs.Accidental().ID())
			        	{
			            	return 1;
			        	}
			        }
			    	return 0;
			    }
			    else
			    {
			        if(lhs.NotePitch() > rhs.NotePitch())
			        {
			            return 1;
			        }
			    }
			    return 0;
			}

			bool MCC_MusicalNote::operator >= (const Note &lhs, const Note &rhs)
			{
			    if(MCC_MusicalNote::CompareMode::CurrentMode == MCC_MusicalNote::CompareMode::Name)
			    {
			        if(lhs.Letter().ID() > rhs.Letter().ID())
			        {
			        	return 1;
			        }
			        else if(lhs.Letter().ID() == rhs.Letter().ID())
			        {
			        	if(lhs.Accidental().ID() >= rhs.Accidental().ID())
			        	{
			            	return 1;
			        	}
			        }
			    	return 0;
			    }
			    else
			    {
			        if(lhs.NotePitch() >= rhs.NotePitch())
			        {
			            return 1;
			        }
			    }
			    return 0;
			}

			bool MCC_MusicalNote::operator == (const MCC_MusicalNote::Note &lhs, const MCC_MusicalNote::Note &rhs)
            {
			    if(MCC_MusicalNote::CompareMode::CurrentMode == MCC_MusicalNote::CompareMode::Name)
			    {
                    if(lhs.Letter().ID() == rhs.Letter().ID())
                    {
                        if(lhs.Accidental().ID() == rhs.Accidental().ID())
                        {
                            return 1;
                        }
                    }
			    }
			    else
			    {
			        if(lhs.NotePitch() == rhs.NotePitch())
			        {
			            return 1;
			        }
			    }
			    return 0;
			}

			bool MCC_MusicalNote::operator != (const Note &lhs, const Note &rhs)
			{
			    if(MCC_MusicalNote::CompareMode::CurrentMode == MCC_MusicalNote::CompareMode::Name)
			    {
			        if((lhs.Letter().ID() == rhs.Letter().ID())&&(lhs.Accidental().ID() == rhs.Accidental().ID()))
			        {
			            return 0;
			        }
			    }
			    else
			    {
			        if(lhs.NotePitch() == rhs.NotePitch())
			        {
			            return 0;
			        }
			    }
			    return 1;
			}


			#if defined (MCC_MUSICAL_INTERVAL_ENABLED)
				Note& Note::operator+=(const MCC_MusicalInterval::Interval &rhs)
				{
				    NoteBuffer = (*this)+rhs;
				    (*this) = NoteBuffer;
				    return (*this);
				}

				Note Note::operator+(const MCC_MusicalInterval::Interval &rhs) const
				{
					MCC_MusicalNote::Note tmp = (*this);
				    
				    int16_t base = NotePitch();
	                
				    if(rhs.Semitones() == MCC_MusicalInterval::InvalidInterval){return tmp;}
				    
				    if(rhs.Number() >= 7)
	                {
	                    tmp.SetOctave(tmp.Octave() + (rhs.Number()/7));
	                }

				    for(uint8_t i = 0; i < rhs.Number()%7; i++)
				    {
				        tmp.Next();
				    }
				    
				    int16_t destination_pitch = (base + rhs.Semitones())%12;
				    int16_t current_pitch = tmp.NotePitch()%12;
				    
				    int8_t distance = current_pitch-destination_pitch;
				    bool flag = 0;
				    
				    if(distance < 0){distance+=12;}
				    if(distance>=6)
				    {
				        flag = 1;
				        distance = destination_pitch-current_pitch;
				        if(distance < 0){distance+=12;}
				    }
				    
				    if(distance == 0){return tmp;}
				    
				    else if(destination_pitch<current_pitch)
				    {
				        if((destination_pitch+distance)%12 == current_pitch)
				        {
				            while( distance != 0 )
				            {
				                if(tmp.Flat() == 0)
				                {
				                    tmp = (*this);
				                    return tmp;
				                }
				                current_pitch = tmp.NotePitch()%12;
				                
				                distance = current_pitch-destination_pitch;
				                if(distance < 0){distance+=12;}
				            }
				            return tmp;
				        }
				        else if((current_pitch+distance)%12 == destination_pitch)
				        {
				            while( distance != 0 )
				            {
				                if(tmp.Sharp() == 0)
				                {
				                    tmp = (*this);
				                    return tmp;
				                }
				                current_pitch = tmp.NotePitch()%12;
				                
				                distance = current_pitch-destination_pitch;
				                if(distance < 0){distance+=12;}
				            }
				            return tmp;
				        }
				    }
				    
				    else if(destination_pitch>current_pitch)
				    {
				        if((destination_pitch+distance)%12 == current_pitch)
				        {
				            while( distance != 0 )
				            {
				                if(tmp.Flat() == 0)
				                {
				                    tmp = (*this);
				                    return tmp;
				                }
				                current_pitch = tmp.NotePitch()%12;
				                
				                distance = current_pitch-destination_pitch;
				                if(distance < 0){distance+=12;}
				            }
				            return tmp;
				        }
				        else if((current_pitch+distance)%12 == destination_pitch)
				        {
				            while( distance != 0 )
				            {
				                if(tmp.Sharp() == 0)
				                {
				                    tmp = (*this);
				                    return tmp;
				                }
				                current_pitch = tmp.NotePitch()%12;
				                
				                distance = current_pitch-destination_pitch;
				                if(distance < 0){distance+=12;}
				            }
				            return tmp;
				        }
				    }

				    return tmp;
				}


				Note& Note::operator-=(const MCC_MusicalInterval::Interval &rhs)
				{
				    MCC_MusicalNote::NoteBuffer = (*this)-rhs;
				    (*this) = MCC_MusicalNote::NoteBuffer;
				    return (*this);
				}

				Note Note::operator-(const MCC_MusicalInterval::Interval &rhs) const
				{
					// Checking if the provided interval is valid, else return the note as is
				    if(rhs.Semitones() == MCC_MusicalInterval::InvalidInterval){return (*this);}

					// Make a copy of this instance into an object called tmp
				    MCC_MusicalNote::Note tmp = (*this);
				    
				    // Storing the base Pitch
				    int16_t base = NotePitch();
				    
				    // Decreasing the octave relative to the Generic Interval from the provided Interval
				    if(rhs.Number() >= 7)
	                {
				    	// initialOctave - (GenericInterval / 7)
	                    tmp.SetOctave(tmp.Octave() - (rhs.Number()/7));
	                }

	                // Changing Note Letter to finish the Generic Interval Conversion
				    for(uint8_t i = 0; i < rhs.Number()%7; i++)
				    {
				        tmp.Previous();
				    }
				    
				    int16_t destination_pitch = base - rhs.Semitones();
				    int16_t current_pitch = tmp.NotePitch();
				    
				    int8_t distance = destination_pitch - current_pitch;

				    if(distance == 0){return tmp;}

				    else if(destination_pitch<current_pitch)
				    {
				        if((destination_pitch-distance) == current_pitch)
				        {
				            while( distance != 0 )
				            {
				                if(tmp.Flat() == 0)
				                {
				                    tmp = (*this);
				                    return tmp;
				                }
				                current_pitch = tmp.NotePitch();
				                
				                distance = destination_pitch-current_pitch;
	                            
				                if(distance > 0){distance-=12;}
				            }
				            return tmp;
				        }
				        else if((current_pitch-distance)%12 == destination_pitch)
				        {
				            while( distance != 0 )
				            {
				                if(tmp.Sharp() == 0)
				                {
				                    tmp = (*this);
				                    return tmp;
				                }
				                current_pitch = tmp.NotePitch()%12;
				                
				                distance = current_pitch-destination_pitch;
				                if(distance < 0){distance+=12;}
				            }
				            return tmp;
				        }
				    }
				    



				    
				    else if(destination_pitch>current_pitch)
				    {
				        if((destination_pitch-distance) == current_pitch)
				        {
				            while( distance != 0 )
				            {
				                if(tmp.Sharp() == 0)
				                {
				                    tmp = (*this);
				                    return tmp;
				                }
				                current_pitch = tmp.NotePitch();
				                
				                distance = current_pitch-destination_pitch;
				                if(distance < 0){distance+=12;}
				            }
				            return tmp;
				        }
				        else if((current_pitch-distance) == destination_pitch)
				        {
				            while( distance != 0 )
				            {
				                if(tmp.Flat() == 0)
				                {
				                    tmp = (*this);
				                    return tmp;
				                }
				                current_pitch = tmp.NotePitch();
				                
				                distance = current_pitch-destination_pitch;
				                if(distance < 0){distance+=12;}
				            }
				            return tmp;
				        }
				    }

				    return tmp;
				}
			#endif
			
		//
		///////////////////////////////////////////////////////////////////////
		// API
			
			const char* Note::Name(const TextFormat& Format)const
			{
			    return Flash::GetName((*this),Format);
			}

			char* Note::Name(char* buff, const TextFormat& Format)
			{
			    return Flash::GetName(buff, (*this), Format);
			}

			const int16_t Note::NotePitch() const
			{
			    Pitch::Letter note = noteData.GetLetter();
			    Pitch::Accidental accidental = noteData.GetAccidental();
			    
			    if((note.ID() != Pitch::Letter::InvalidID)||(accidental >= Pitch::Accidental::MinIterator)||(accidental <= Pitch::Accidental::MaxIterator))
			    {
					int16_t note_pitch = MusicalNote::NotesArray[note.ID()] + accidental.ID() + (octave * 12);

					if ((note == MusicalNote::Pitch::Letter::B) && (accidental >= MusicalNote::Pitch::Accidental::Sharp)) { return note_pitch - 12; }
					if ((note == MusicalNote::Pitch::Letter::A) && (accidental >= MusicalNote::Pitch::Accidental::TripleSharp)) { return note_pitch - 12; }
					return note_pitch;
			    }
			    else
			    {
					return MusicalNote::InvalidPitch;
			    }
			}

			const uint8_t Note::MidiPitch() const
			{
			    uint8_t note_pitch = NotePitch();
			    if((note_pitch < 0)||(note_pitch>127))
			    {
			        return 0xFF;
			    }
			    return note_pitch;
			}

			const float Note::Frequency( const Note& ReferenceNote, float ReferenceFrequeny) const
			{
				int16_t semitones = NotePitch() - ReferenceNote.NotePitch();
				float freq = ReferenceFrequeny * pow(2.0, (semitones / 12.0));

				return freq;
			}
 

			///////////////////////////////////////////////////////////////////
			// Octaves

				void Note::SetOctave(int8_t Octave)
				{
				    octave = Octave+2;
				}

				void Note::OctaveUp()
				{
				    octave++;
				}

				void Note::OctaveDown()
				{
				    octave--;
				}

				const int8_t Note::Octave() const
				{
					return octave-2;
				}
			//
			///////////////////////////////////////////////////////////////////
			// Pitch

				void Note::SetPitch(const MusicalNote::Pitch& src)
				{
					noteData = src;
				}

				const Pitch& Note::GetPitch() const
				{
					return noteData;
				}

				///////////////////////////////////////////////////////////////
				// Accidental

                    void Note::SetAccidental(const Pitch::Accidental& src)
					{
						noteData.SetAccidental(src);
					}

					const Pitch::Accidental& Note::Accidental() const
					{
						return noteData.GetAccidental();
					}

					bool Note::Flat()
					{
					    return noteData.Flat();
					}

					bool Note::Sharp()
					{
					    return noteData.Sharp();
					}
				//
				///////////////////////////////////////////////////////////////
				// Letter


                    void Note::SetLetter(const Pitch::Letter& src)
					{
						noteData.SetLetter(src);
					}

					const Pitch::Letter& Note::Letter() const
					{
						return noteData.GetLetter();
					}

					void Note::Next()
					{
					    noteData.Next();
					    if(noteData.GetLetter() == Pitch::Letter::C)
					    {
					        octave++;
					    }
					}

					void Note::Previous()
					{
					    noteData.Previous();
					    if(noteData.GetLetter() == Pitch::Letter::B)
					    {
					        octave--;
					    }
					}
				//
				///////////////////////////////////////////////////////////////	
			//
			///////////////////////////////////////////////////////////////////
		//
		///////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////