#ifndef MCC_SCALE_CLASS_H
#define MCC_SCALE_CLASS_H

    #include <MCC_BuildSettings.h>
    #include <CPVector.h>
    #include <CPString.h>

    #include "../MusicalNote/MusicalNote.h"
    #include "../MusicalInterval/MusicalInterval.h"
    #include "ScaleProperties/ScaleProperties.h"
    #include "ScaleFlash/ScaleFlash.h"

    namespace MusicCompositionCore
    {
        namespace Core
        {
            namespace MusicalCore
            {
                namespace MusicalScale
                {
                    extern CPString::string DefaultName;
                    
                    namespace Flash
                    {
                        struct Container;
                        struct Container_Notes;
                        struct Container_Mapping;
                    }

                    class Scale
                    {
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Variable Declaration

                            CPString::string _UserName;

                            PropertiesContainer _Data;

                            uint8_t _NameID;
                            uint8_t _RootOffset;
                            
                            CPVector::vector<MCC_MusicalNote::Pitch::PitchClass> _Notes;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                        public:

                            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // Constructors - Destructors
                            
                                Scale(bool sharps_flats = 0);

                                Scale(const CPVector::vector<MCC_MusicalNote::Note> &notes, CPString::string& name = DefaultName);
                                Scale(const CPVector::vector<MCC_MusicalNote::Pitch::PitchClass> &noteTokens, CPString::string& name = DefaultName);

                                Scale(const MCC_MusicalNote::Note &root, const CPVector::vector<MCC_MusicalInterval::Interval> &intervals, CPString::string& name = DefaultName);
                                Scale(const MCC_MusicalNote::Pitch::PitchClass &root, const CPVector::vector<MCC_MusicalInterval::Interval> &intervals, CPString::string& name = DefaultName);
                                Scale(const MCC_MusicalNote::Pitch::PitchClass &root, const MCC_MusicalInterval::Interval* intervals, uint8_t size, CPString::string& name = DefaultName);
                                
                                Scale(uint8_t root, const Flash::Container_Notes& source);
                                Scale(const Flash::Container_Notes& source);
                                Scale(const MCC_MusicalNote::Note& root, const Flash::Container_Notes& source);
                                Scale(const MCC_MusicalNote::Pitch::PitchClass& root, const Flash::Container_Notes& source);

                                Scale(const MCC_MusicalNote::Note &root, const Flash::Container_Mapping& source);
                                Scale(const MCC_MusicalNote::Pitch::PitchClass& root, const Flash::Container_Mapping& source);

                                Scale(const MCC_MusicalNote::Note &root, const Flash::Container* source, uint8_t ID);
                                Scale(const MCC_MusicalNote::Pitch::PitchClass& root, const Flash::Container* source, uint8_t ID);

                                Scale(const MCC_MusicalNote::Note &root, uint8_t ID);
                                Scale(const MCC_MusicalNote::Pitch::PitchClass&root, uint8_t ID); 
                                
                                ~Scale();
                            //
                            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // Operators

                                Scale& operator =(const Scale& source);
                                const MCC_MusicalNote::Note& operator()(uint8_t note, uint8_t octave);
                                const MCC_MusicalNote::Note& operator[](uint8_t note);
                            //
                            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // API

                                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                // Name 

                                    const char* Name() const;
                                    char* Name(char* buff) const;
                                    void SetName(CPString::string& new_name);
                                //
                                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                // Note Token Vector

                                    const CPVector::vector<MCC_MusicalNote::Pitch::PitchClass>& NoteTokenVector() const;
                                    const uint8_t size() const;
                                //
                                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                // Root Note

                                    void SetRootNote(const MCC_MusicalNote::Note& root);
                                    void SetRootNote(const MCC_MusicalNote::Pitch::PitchClass& root);

                                    const MCC_MusicalNote::Note RootNote() const;
                                //
                                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                // Root Offset

                                    void SetRootOffset(uint8_t Offset);
                                    void SetRootOffset(const MCC_MusicalNote::Note& newRoot);
                                    void SetRootOffset(const MCC_MusicalNote::Pitch::PitchClass& newRoot);

                                    const uint8_t RootOffset() const; 
                                //
                                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                // Interval

                                    const MCC_MusicalInterval::Interval Interval(uint8_t x) const;
                                    const MCC_MusicalInterval::Interval Interval(uint8_t a, uint8_t b) const;
                                //
                                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                // Note

                                    const MCC_MusicalNote::Note Note(int16_t x) const;
                                //
                                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                // PropertiesContainer

                                    const PropertiesContainer& Properties() const;

                                    const bool MappingMode() const;
                                    void SetMappingMode(bool mapping_mode);
                                    
                                    const uint8_t Location() const;
                                    void SetLocation(uint8_t scale_location);
                                    
                                    const bool NameFlag() const;
                                    void SetNameFlag(bool name_flag);
                                //
                                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                // ScaleID
                                    
                                    void SetScaleID(uint8_t ID);
                                    const uint8_t ScaleID() const;
                                //
                                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //
                            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                        private:

                            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // Private Methods
                                
                                void _SortNotes();
                            //
                            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                        };

                        
                }
            }
        }
    }



#endif//MCC_SCALE_CLASS_H