#include "MusicalScale.h"

cpstd::string MusicCompositionCore::MusicalScale::DefaultName("No Name");
cpstd::string MusicCompositionCore::MusicalScale::NameBuffer("");

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

        MCC_MusicalScale::Scale::Scale(const cpstd::vector<MCC_MusicalNote::Note> &Notes, cpstd::string& name): _Data(0)
        {
            _Notes.resize(Notes.size());
            _RootOffset = 0;
            
            for(uint8_t i = 0; i < Notes.size(); i++)
            {
                _Notes[i] = Notes[i].GetPitch();
            }
            
            _SortNotes();
            _UserName = name;
            
            _Data.SetLocation(ScaleProperties::Location::None);
            _Data.SetNameFlag(ScaleProperties::NameFlag::User);
            _Data.SetMappingMode(ScaleProperties::MappingMode::Dynamic);
        }

        MCC_MusicalScale::Scale::Scale(const cpstd::vector<MCC_MusicalNote::Pitch> &Tokens, cpstd::string& name): _Data(0)
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

        MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Note& root, const cpstd::vector<MCC_MusicalInterval::Interval>& intervals, cpstd::string &name) : _Data(0)
        {
            _Notes.resize(intervals.size() + 1);
            
            _Notes[0] = root.GetPitch();
            _RootOffset = 0;
            
            for(uint8_t i = 0; i < intervals.size(); i++)
            {
                _Notes[1 + i] = (MCC_MusicalNote::Note(_Notes[0],intervals[i]).GetPitch());
            }
            
            _SortNotes();
            _UserName = name;
            _Data.SetLocation(ScaleProperties::Location::None);
            _Data.SetNameFlag(ScaleProperties::NameFlag::User);
            _Data.SetMappingMode(ScaleProperties::MappingMode::Fixed);
        }

        MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch& root, const cpstd::vector <MCC_MusicalInterval::Interval>& intervals, cpstd::string & name) : _Data(0)
        {
            _Notes.resize(intervals.size() + 1);
            
            _Notes[0] = root;
            _RootOffset = 0;
            
            for(uint8_t i = 0; i < intervals.size(); i++)
            {
                _Notes[1 + i] = (MCC_MusicalNote::Note(_Notes[0],intervals[i]).GetPitch());
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

            MCC_MusicalScale::Scale::Scale(const Flash::Container_Notes& source): _Data(0)
            {
                uint8_t count = 0;

                _Data = Flash::GetScaleProperties(source);
                _NameID = Flash::GetScaleID(source);

                while(Flash::GetScaleNoteToken(source,count) != MCC_MusicalNote::Pitch::InvaildPitch)
                {
                    count++;
                    if(count == 12){break;}
                }

                _Notes.resize(count);

                _RootOffset = 0;

                for(uint8_t i = 0; i < _Notes.size(); i++)
                {
                    MCC_MusicalNote::Pitch Pitch = MCC_MusicalNote::Pitch(Flash::GetScaleNoteToken(source,i));
                    _Notes[i] = Pitch;
                }

                _SortNotes();

                _Data.SetLocation(ScaleProperties::Location::Flash);
                _Data.SetNameFlag(ScaleProperties::NameFlag::System);
                _Data.SetMappingMode(ScaleProperties::MappingMode::Dynamic);
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch& root, const Flash::Container_Notes& source): _Data(0)
            {
                *this = Scale(source);

                for(uint8_t i = 0; i < _Notes.size(); i++)
                {
                    if(_Notes[i] == root){_RootOffset = i;}
                }
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch::Type& root, const Flash::Container_Notes& source): _Data(0)
            {
                *this = Scale(source);
                auto Root = MCC_MusicalNote::Pitch(root);


                for(uint8_t i = 0; i < _Notes.size(); i++)
                {
                    if(_Notes[i] == Root){_RootOffset = i;}
                }
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Note& root, const Flash::Container_Notes& source): _Data(0)
            {
                *this = Scale(source);

                for(uint8_t i = 0; i < _Notes.size(); i++)
                {
                    if(_Notes[i] == root.GetPitch()){_RootOffset = i;}
                }
            }
        //
        //////////////////////////////////////////////////////////////////////////////////////////////
        // FlashContainer Mapping
        
            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch::Type& root, const Flash::Container_Mapping& source): _Data(0)
            {
                uint16_t mapping = Flash::GetScaleMapping(source);
                auto Root = MCC_MusicalNote::Pitch(root);
                
                _Notes.resize(mapping>>12);
                
                _Data = Flash::GetScaleProperties(source);
                _NameID = Flash::GetScaleID(source);
                
                _RootOffset = 0;
                
                _Notes[0] = Root;
                
                uint8_t count = 1;
                MCC_MusicalInterval::Interval interval;

                for(uint8_t i = 1; i < _Notes.size(); i++)
                {
                    while(((mapping>>(11-count)) & 1u) != 1){count++;}

                    interval = MCC_MusicalInterval::Interval(Root.NotePitch(),Root.NotePitch()+count,Flash::GetScaleGenericInterval(source,i-1));
                    
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
            
            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch &root, const Flash::Container_Mapping& source): _Data(0)
            {
                (*this) = Scale(root.ID(), source);
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Note &root, const Flash::Container_Mapping& source): _Data(0)
            {
                (*this) = Scale(root.GetPitch().ID(), source);
            }
        //
        //////////////////////////////////////////////////////////////////////////////////////////////
        // FlashContainer*

             MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch& root, const Flash::Container* source, uint8_t ID): _Data(0)
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
                (*this) = Scale(root.GetPitch(),source,ID);
            }

            MCC_MusicalScale::Scale::Scale(const MCC_MusicalNote::Pitch &root, uint8_t ID): _Data(0)
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
                (*this) = Scale(root.GetPitch(), ID);
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

        void MCC_MusicalScale::Scale::SetName(cpstd::string& new_name)
        {
            _UserName = new_name;
            _Data.SetNameFlag(ScaleProperties::NameFlag::User);
        }

        const char* MCC_MusicalScale::Scale::Name() const
        {
            if(_Data.NameFlag() == ScaleProperties::NameFlag::User)
            { 
                NameBuffer = RootNote().GetPitch().Name();
                NameBuffer += " ";
                NameBuffer += _UserName;
                return NameBuffer.c_str();
            }
                
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

        const cpstd::vector<MCC_MusicalNote::Pitch>& MCC_MusicalScale::Scale::NoteTokenVector() const
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
        
        void MCC_MusicalScale::Scale::SetRootNote(const MCC_MusicalNote::Pitch& root)
        {
            if(_Notes[_RootOffset] == root){return;}

            if(_Data.MappingMode() == ScaleProperties::MappingMode::Fixed)
            {

                if(_Data.Location() == ScaleProperties::Location::None)
                {
                    cpstd::vector<MCC_MusicalInterval::Interval> Intervals;
                    Intervals.resize(size() - 1);

                    for(uint8_t i = 1; i < size(); i++)
                    {
                        Intervals[i-1] = Interval(_RootOffset+i);
                    }

                    cpstd::string name = DefaultName;

                    if(_Data.NameFlag() == ScaleProperties::NameFlag::User)
                    {
                        name = _UserName;
                    }

                    (*this) = Scale(root, Intervals);

                    if(name != DefaultName)
                    {
                        SetName(name);
                    }
                }
                else if(_Data.Location() == ScaleProperties::Location::Flash)
                {
                    cpstd::string name = DefaultName;

                    if(_Data.NameFlag() == ScaleProperties::NameFlag::User)
                    {
                        name = _UserName;
                    }

                    (*this) = Scale(root,_NameID);

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
                    if(Note(i).GetPitch() == root)
                    {
                        SetRootOffset(i);
                    }
                }
            }
        }

        void MCC_MusicalScale::Scale::SetRootNote(const MCC_MusicalNote::Note& root)
        {
            SetRootNote(root.GetPitch());
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
                if(_Notes[i] == newRoot.GetPitch())
                {
                    SetRootOffset(i);
                }
            }
        }

        void MCC_MusicalScale::Scale::SetRootOffset(const MCC_MusicalNote::Pitch& newRoot)
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

                cpstd::string name = DefaultName;

                if(_Data.NameFlag() == ScaleProperties::NameFlag::User)
                {
                    name = _UserName;
                }


                (*this) = Scale(_Notes[_RootOffset], ID);


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
        MCC_MusicalNote::Pitch tmp = _Notes[_RootOffset];
        cpstd::sort(_Notes.begin(), _Notes.end(), MCC_MusicalNote::Sorting::Pitch::NotePitch_Ascending);
        
        for(size_t i = 0; i < _Notes.size(); i++)
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
