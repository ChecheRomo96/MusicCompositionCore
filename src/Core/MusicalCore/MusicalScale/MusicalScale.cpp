#include "MusicalScale.h"

CPString::string MusicCompositionCore::Core::MusicalCore::MusicalScale::DefaultName("No Name");

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor, Destructor
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Default Constructor

        MCC_MusicalScale::Scale::Scale(bool sharps_flats): _Data(0)
        {
            // Default Scale is Chromatic
            if(sharps_flats == 0)
            {
                (*this) = Scale(Flash::Scales::Chromatic);
            }
            else
            {
                (*this) = Scale(Flash::Scales::Chromatic_Flats);
            }
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Note Vector, Note PitchClass() Vector

        MCC_MusicalScale::Scale::Scale(const CPVector::vector<MCC_MusicalNote::Note> &Notes, CPString::string& name): _Data(0)
        {
            _Notes.resize(Notes.size());
            _RootOffset = 0;
            
            for(uint8_t i = 0; i < Notes.size(); i++)
            {
                _Notes[i] = Notes[i].Pitch();
            }
            
            _SortNotes();
            _UserName = name;
            
            _Data.SetLocation(ScaleProperties::Location::None);
            _Data.SetNameFlag(ScaleProperties::NameFlag::User);
            _Data.SetMappingMode(ScaleProperties::MappingMode::Dynamic);
        }

        MCC_MusicalScale::Scale::Scale(const CPVector::vector<MCC_MusicalNote::Pitch::PitchClass> &Tokens, CPString::string& name): _Data(0)
        {
            _Notes.resize(Tokens.size());
            _RootOffset = 0;
            
            for(uint8_t i = 0; i < Tokens.size(); i++)
            {
                _Notes[i] = Tokens[i];
            }
            
            _SortNotes();
            _UserName = name;
            _Data.SetLocation(ScaleProperties::Location::None);
            _Data.SetNameFlag(ScaleProperties::NameFlag::User);
            _Data.SetMappingMode(ScaleProperties::MappingMode::Dynamic);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Note + Interval Vector

        MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Note& root, const CPVector::vector<MCC_MusicalInterval::Interval>& intervals, CPString::string &name) : _Data(0)
        {
            _Notes.resize(intervals.size() + 1);
            
            _Notes[0] = root.Pitch();
            _RootOffset = 0;
            
            for(uint8_t i = 0; i < intervals.size(); i++)
            {
                _Notes[1 + i] = (MCC_MusicalNote::Note(_Notes[0],intervals[i]).Pitch());
            }
            
            _SortNotes();
            _UserName = name;
            _Data.SetLocation(ScaleProperties::Location::None);
            _Data.SetNameFlag(ScaleProperties::NameFlag::User);
            _Data.SetMappingMode(ScaleProperties::MappingMode::Fixed);
        }

        MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch::PitchClass& root, const CPVector::vector <MCC_MusicalInterval::Interval>& intervals, CPString::string & name) : _Data(0)
        {
            _Notes.resize(intervals.size() + 1);
            
            _Notes[0] = root;
            _RootOffset = 0;
            
            for(uint8_t i = 0; i < intervals.size(); i++)
            {
                _Notes[1 + i] = (MCC_MusicalNote::Note(_Notes[0],intervals[i]).Pitch());
            }
            
            _SortNotes();
            _UserName = name;
            _Data.SetLocation(ScaleProperties::Location::None);
            _Data.SetNameFlag(ScaleProperties::NameFlag::User);
            _Data.SetMappingMode(ScaleProperties::MappingMode::Fixed);
        }

        MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch::PitchClass& root, const MCC_MusicalInterval::Interval* intervals, uint8_t intervals_size, CPString::string &name) : _Data(0)
        {
            _Notes.resize(intervals_size + 1);
            
            _Notes[0] = root;
            _RootOffset = 0;
            
            for(uint8_t i = 0; i < intervals_size; i++)
            {
                _Notes[1 + i] = (MCC_MusicalNote::Note(_Notes[0],intervals[i]).Pitch());
            }
            
            _SortNotes();
            _UserName = name;
            _Data.SetLocation(ScaleProperties::Location::None);
            _Data.SetNameFlag(ScaleProperties::NameFlag::User);
            _Data.SetMappingMode(ScaleProperties::MappingMode::Fixed);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Flash

        //////////////////////////////////////////////////////////////////////////////////////////////
        // FlashContainer Notes

            MCC_MusicalScale::Scale::Scale(uint8_t root, const Flash::Container_Notes& source): _Data(0)
            {
                uint8_t count = 0;

                _Data = Flash::GetScaleProperties(source);
                _NameID = Flash::GetScaleID(source);

                while(Flash::GetScaleNoteToken(source,count) != MCC_MusicalNote::Pitch::Count)
                {
                    count++;
                    if(count == 12){break;}
                }

                _Notes.resize(count);

                _RootOffset = root;

                for(uint8_t i = 0; i < _Notes.size(); i++)
                {
                    MCC_MusicalNote::Pitch::PitchClass PitchClass = MCC_MusicalNote::Pitch::PitchClass(Flash::GetScaleNoteToken(source,i));
                    _Notes[i] = PitchClass;
                }

                _SortNotes();

                _Data.SetLocation(ScaleProperties::Location::Flash);
                _Data.SetNameFlag(ScaleProperties::NameFlag::System);
                _Data.SetMappingMode(ScaleProperties::MappingMode::Dynamic);
            }

            MCC_MusicalScale::Scale::Scale(const Flash::Container_Notes& source): _Data(0)
            {
                uint8_t count = 0;

                _Data = Flash::GetScaleProperties(source);
                _NameID = Flash::GetScaleID(source);

                while(Flash::GetScaleNoteToken(source,count) != MCC_MusicalNote::Pitch::Count)
                {
                    count++;
                    if(count == 12){break;}
                }

                _Notes.resize(count);

                _RootOffset = 0;

                for(uint8_t i = 0; i < _Notes.size(); i++)
                {
                    MCC_MusicalNote::Pitch::PitchClass PitchClass = MCC_MusicalNote::Pitch::PitchClass(Flash::GetScaleNoteToken(source,i));
                    _Notes[i] = PitchClass;
                }

                _SortNotes();

                _Data.SetLocation(ScaleProperties::Location::Flash);
                _Data.SetNameFlag(ScaleProperties::NameFlag::System);
                _Data.SetMappingMode(ScaleProperties::MappingMode::Dynamic);
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch::PitchClass& root, const Flash::Container_Notes& source): _Data(0)
            {
                *this = Scale(source);

                for(uint8_t i = 0; i < _Notes.size(); i++)
                {
                    if(_Notes[i] == root){_RootOffset = i;}
                }
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Note& root, const Flash::Container_Notes& source): _Data(0)
            {
                *this = Scale(source);

                for(uint8_t i = 0; i < _Notes.size(); i++)
                {
                    if(_Notes[i] == root.Pitch()){_RootOffset = i;}
                }
            }
        //
        //////////////////////////////////////////////////////////////////////////////////////////////
        // FlashContainer Mapping
        
            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch::PitchClass& root, const Flash::Container_Mapping& source): _Data(0)
            {
                uint16_t mapping = Flash::GetScaleMapping(source);
                
                _Notes.resize(mapping>>12);
                
                _Data = Flash::GetScaleProperties(source);
                _NameID = Flash::GetScaleID(source);
                
                _RootOffset = 0;
                
                _Notes[0] = root;
                
                uint8_t count = 1;
                MCC_MusicalInterval::Interval interval;

                for(uint8_t i = 1; i < _Notes.size(); i++)
                {
                    while(((mapping>>(11-count)) & 1u) != 1){count++;}

                    interval = MCC_MusicalInterval::Interval(root.NotePitch(),root.NotePitch()+count,Flash::GetScaleGenericInterval(source,i-1));
                    
                    _Notes[i] = _Notes[0] + interval;

                    if(_Notes[i] == _Notes[0])
                    {
                        _Notes.clear();
                        (*this) = MCC_MusicalScale::Scale();
                        return;
                    }
                    count++;
                }
                
                _SortNotes();

                _Data.SetLocation(ScaleProperties::Location::Flash);
                _Data.SetNameFlag(ScaleProperties::NameFlag::System);
                _Data.SetMappingMode(ScaleProperties::MappingMode::Fixed);
            }
            
            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Note &root, const Flash::Container_Mapping& source): _Data(0)
            {
                (*this) = Scale(root.Pitch(),source);
            }
        //
        //////////////////////////////////////////////////////////////////////////////////////////////
        // FlashContainer*

             MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch::PitchClass& root, const Flash::Container* source, uint8_t ID): _Data(0)
            {
                if(ID >= MCC_MusicalScale::Flash::ScaleArrays::Flash_Size)
                {
                    (*this) = Scale();
                    return;
                }

                const MCC_MusicalScaleFlash::Container_Notes* ptr1 = source[ID].NotesPointer;
                const MCC_MusicalScaleFlash::Container_Mapping* ptr2 = source[ID].MappingPointer;


                if(ptr1 != NULL)
                {
                    (*this) = Scale(root,*ptr1);
                    return;
                }
                else if(ptr2 != NULL)
                {
                    (*this) = Scale(root,*ptr2);
                    return;
                }
                else
                {
                    (*this) = Scale();
                    return;
                }
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Note &root, const Flash::Container* source, uint8_t ID): _Data(0)
            {
                (*this) = Scale(root.Pitch(),source,ID);
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch::PitchClass &root, uint8_t ID): _Data(0)
            {

                if(ID < MCC_MusicalScale::Flash::ScaleArrays::Flash_Size)
                {
                     (*this) = Scale(root,MCC_MusicalScale::Flash::ScaleArrays::Flash,ID);
                }
                else
                {
                    (*this) = Scale();
                }
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Note &root, uint8_t ID): _Data(0)
            {
                (*this) = Scale(ID,root.Pitch());
            }
        //
        //////////////////////////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor
        
        MCC_MusicalScale::Scale::~Scale()
        {
            _Notes.clear();
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//  Operators

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Copy Constructor operator

        MCC_MusicalScale::Scale& MCC_MusicalScale::Scale::operator =(const Scale& source)
        {
            _Notes.clear();
            _Data = source.Properties();
            _NameID = source.ScaleID();
            _Notes.resize(source.NoteTokenVector().size());
            _RootOffset = source.RootOffset();

            for(uint8_t i = 0; i < _Notes.size(); i++)
            {
                _Notes[i] = source.NoteTokenVector()[i];
            }
            
            return (*this);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Function Call Operator

        const MCC_MusicalNote::Note& MCC_MusicalScale::Scale::operator()(uint8_t note,uint8_t octave)
        {
            MCC_MusicalNote::NoteBuffer = Note(note);
            MCC_MusicalNote::NoteBuffer.SetOctave(octave+((note-RootOffset())/size()));
            return MCC_MusicalNote::NoteBuffer;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Subscript Array Operator

        const MCC_MusicalNote::Note& MCC_MusicalScale::Scale::operator[](uint8_t note)
        {
            MCC_MusicalNote::NoteBuffer = Note(note);
            return MCC_MusicalNote::NoteBuffer;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//  API

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Name 

        void MCC_MusicalScale::Scale::SetName(CPString::string& new_name)
        {
            _UserName = new_name;
            _Data.SetNameFlag(ScaleProperties::NameFlag::User);
        }

        const char* MCC_MusicalScale::Scale::Name() const
        {
            
            if(_Data.NameFlag() == ScaleProperties::NameFlag::User){ return _UserName.c_str(); }
                
            switch(_Data.Location())
            {
                case ScaleProperties::Location::Flash: return Flash::GetScaleName(_Notes[_RootOffset], _NameID);
                case ScaleProperties::Location::EEPROM: break;
            }
            return DefaultName.c_str();
        }

        char* MCC_MusicalScale::Scale::Name(char* buff) const
        {
            return Flash::GetScaleName(buff,_Notes[_RootOffset], _NameID);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Note PitchClass() Vector

        const CPVector::vector<MCC_MusicalNote::Pitch::PitchClass>& MCC_MusicalScale::Scale::NoteTokenVector() const
        {
            return _Notes;
        }

        const uint8_t MCC_MusicalScale::Scale::size() const
        {
            return _Notes.size();
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Root Note 
        
        void MCC_MusicalScale::Scale::SetRootNote(const MCC_MusicalNote::Pitch::PitchClass& root)
        {
            if(_Notes[_RootOffset] == root){return;}

            if(_Data.MappingMode() == ScaleProperties::MappingMode::Fixed)
            {

                if(_Data.Location() == ScaleProperties::Location::None)
                {
                    CPVector::vector<MCC_MusicalInterval::Interval> Intervals;
                    Intervals.resize(size() - 1);

                    for(uint8_t i = 1; i < size(); i++)
                    {
                        Intervals[i-1] = Interval(_RootOffset+i);
                    }

                    CPString::string name = DefaultName;

                    if(_Data.NameFlag() == ScaleProperties::NameFlag::User)
                    {
                        name = _UserName;
                    }

                    (*this) = Scale(root,Intervals,size()-1);

                    if(name != DefaultName)
                    {
                        SetName(name);
                    }
                }
                else if(_Data.Location() == ScaleProperties::Location::Flash)
                {
                    CPString::string name = DefaultName;

                    if(_Data.NameFlag() == ScaleProperties::NameFlag::User)
                    {
                        name = _UserName;
                    }

                    (*this) = Scale(_NameID,root);

                    if(name != DefaultName)
                    {
                        SetName(name);
                    }
                }

            }
            else
            {
                for(uint8_t i = 0; i < size(); i++)
                {
                    if(Note(i).Pitch() == root)
                    {
                        SetRootOffset(i);
                    }
                }
            }
        }

        void MCC_MusicalScale::Scale::SetRootNote(const MCC_MusicalNote::Note& root)
        {
            SetRootNote(root.Pitch());
        }
        
        const MCC_MusicalNote::Note MCC_MusicalScale::Scale::RootNote() const
        {
            return _Notes[_RootOffset];
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Root Offset 
                                    
        void MCC_MusicalScale::Scale::SetRootOffset(uint8_t Offset)
        {
            if(_Data.MappingMode() == ScaleProperties::MappingMode::Dynamic)
            {
                if(Offset < size())
                {
                    _RootOffset = Offset;
                }
            }
        }

        void MCC_MusicalScale::Scale::SetRootOffset(const MCC_MusicalNote::Note& newRoot)
        {
            for(uint8_t i = 0; i < size(); i++)
            {
                if(_Notes[i] == newRoot.Pitch())
                {
                    SetRootOffset(i);
                }
            }
        }

        void MCC_MusicalScale::Scale::SetRootOffset(const MCC_MusicalNote::Pitch::PitchClass& newRoot)
        {
            for(uint8_t i = 0; i < size(); i++)
            {
                if(_Notes[i] == newRoot)
                {
                    SetRootOffset(i);
                }
            }
        }

        const uint8_t MCC_MusicalScale::Scale::RootOffset() const
        {
            return _RootOffset;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Interval 

        const MCC_MusicalInterval::Interval MCC_MusicalScale::Scale::Interval(uint8_t x) const
        {
            return MCC_MusicalInterval::Interval(Note(_RootOffset),Note(x));
        }

        const MCC_MusicalInterval::Interval MCC_MusicalScale::Scale::Interval(uint8_t a, uint8_t b) const
        {
            return MCC_MusicalInterval::Interval(Note(a),Note(b));
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Note 

        const MCC_MusicalNote::Note MCC_MusicalScale::Scale::Note(int16_t x) const
        {
            MCC_MusicalNote::NoteBuffer = _Notes[x%_Notes.size()];
            MCC_MusicalNote::NoteBuffer.SetOctave(x/_Notes.size()-2);
            return MCC_MusicalNote::NoteBuffer;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties Conatiner 

        const MCC_MusicalScale::PropertiesContainer& MCC_MusicalScale::Scale::Properties() const
        {
            return _Data;
        }


        const bool MCC_MusicalScale::Scale::MappingMode() const
        {
            return _Data.MappingMode();
        }

        void MCC_MusicalScale::Scale::SetMappingMode(bool mapping_mode)
        {
            _Data.SetMappingMode(mapping_mode);
        }

        
        const uint8_t MCC_MusicalScale::Scale::Location() const
        {
            return _Data.Location();
        }

        void MCC_MusicalScale::Scale::SetLocation(uint8_t scale_location)
        {
            _Data.SetLocation(scale_location);
        }

        
        const bool MCC_MusicalScale::Scale::NameFlag() const
        {
            return _Data.NameFlag();
        }

        void MCC_MusicalScale::Scale::SetNameFlag(bool name_flag)
        {
            _Data.SetNameFlag(name_flag);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // ScaleID 
                                    
        void MCC_MusicalScale::Scale::SetScaleID(uint8_t ID)
        {
            if(Location() == ScaleProperties::Location::Flash)
            {
                if(ID >= MCC_MusicalScale::Flash::ScaleArrays::Flash_Size){return;}

                CPString::string name = DefaultName;

                if(_Data.NameFlag() == ScaleProperties::NameFlag::User)
                {
                    name = _UserName;
                }


                (*this) = Scale(ID,_Notes[_RootOffset]);


                if(name != DefaultName)
                {
                    SetName(name);
                }
            }
        }

        const uint8_t MCC_MusicalScale::Scale::ScaleID() const
        {
            return _NameID;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods

    void MCC_MusicalScale::Scale::_SortNotes()
    {
        if(_Notes.size() == 0){return;}
        MCC_MusicalNote::Pitch::PitchClass tmp = _Notes[_RootOffset];
        
        CPVector::Sorting::SortingArray<MCC_MusicalNote::Pitch::PitchClass> sortSettings;
        sortSettings.Append(MCC_MusicalNote::Sorting::PitchClass::NotePitch_Ascending);
        _Notes.Sort(sortSettings);
        
        for(uint8_t i = 0; i < _Notes.size(); i++)
        {
            if(_Notes[i] == tmp)
            {
                _RootOffset = i;
                break;
            }
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
