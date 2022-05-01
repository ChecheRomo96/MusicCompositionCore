#include "IntervalFlash.h" 
#include <string.h>

using namespace MusicCompositionCore::Core::MusicalCore::MusicalInterval;

char MusicCompositionCore::Core::MusicalCore::MusicalInterval::Flash::buffer[41];

uint8_t Flash::GetIntervalSemitones(uint8_t IntervalType, uint8_t IntervalQuality)
{
	uint8_t intervalType = IntervalType % 7;
	uint8_t octaves = IntervalType / 7;

	int8_t semitones;

	if((IntervalType == Numbers::Prime) && (IntervalQuality < Qualities::Perfect))
	{
		return InvalidInterval;
	}

	if(IntervalQuality < 4)
	{
		#if defined(__AVR__)
			semitones = pgm_read_byte(&(IntervalMap[intervalType][0]));
		#else
			semitones = IntervalMap[intervalType][0];
		#endif

		if((uint8_t)semitones == InvalidInterval)
		{
			#if defined(__AVR__)
				semitones = pgm_read_byte(&(IntervalMap[intervalType][1]));
			#else
				semitones = IntervalMap[intervalType][1];
			#endif
		}

		semitones-=(4-IntervalQuality);
		
	}
	else if(IntervalQuality > 6)
	{
		#if defined(__AVR__)
			semitones = pgm_read_byte(&(IntervalMap[intervalType][2]));
		#else
			semitones = IntervalMap[intervalType][2];
		#endif

		if((uint8_t)semitones == InvalidInterval)
		{
			#if defined(__AVR__)
				semitones = pgm_read_byte(&(IntervalMap[intervalType][1]));
			#else
				semitones = IntervalMap[intervalType][1];
			#endif
		}

		semitones+=(IntervalQuality-6);
	}
	else
	{
		#if defined(__AVR__)
			semitones = pgm_read_byte(&(IntervalMap[intervalType][IntervalQuality-4]));
		#else
			semitones = IntervalMap[intervalType][IntervalQuality-4];
		#endif
        if((uint8_t)semitones == InvalidInterval)
        {
            return InvalidInterval;
        }
	}

	if(semitones + (octaves*12)<0){return InvalidInterval;}
	return semitones + (octaves*12);
}


const char* Flash::GetGenericIntervalStr(uint8_t IntervalType)
{
	return GetGenericIntervalStr(buffer, IntervalType);
}

char* Flash::GetGenericIntervalStr(char* buff, uint8_t IntervalType)
{
	if(IntervalType < Numbers::Count)
	{
		#if defined(__AVR__)
			strcpy_P(buff,pgm_read_word(&(GenericIntervalNames[IntervalType])));
		#else
			strcpy(buff,GenericIntervalNames[IntervalType]);
		#endif
	}
	else
	{	
		#if defined(__AVR__)
            strcpy_P(buff,pgm_read_word(GenericIntervalNames[Numbers::Count]));
            uint8_t offset = strlen(buff);
            buff[offset] = ' ';
            if(IntervalType%7 == 0)
            {
                strcpy_P(&buff[offset+1],pgm_read_word(GenericIntervalNames[7]));
            }
            else
            {
                strcpy_P(&buff[offset+1],pgm_read_word(GenericIntervalNames[IntervalType%7]));
            }
        
        #else
	        strcpy(buff,GenericIntervalNames[Numbers::Count]);
	        uint8_t offset = strlen(buff);
	        buff[offset] = ' ';
            if(IntervalType%7 == 0)
            {
                strcpy(&buff[offset+1],GenericIntervalNames[7]);
            }
            else
            {
                strcpy(&buff[offset+1],GenericIntervalNames[IntervalType%7]);
            }
        
		#endif
	}
	return buff;
}

const char* Flash::GetIntervalQualityStr(uint8_t IntervalQuality)
{
	return GetIntervalQualityStr(buffer,IntervalQuality);
}

char* Flash::GetIntervalQualityStr(char* buff, uint8_t IntervalQuality)
{
	if(IntervalQuality < Qualities::Count)
	{
	    #if defined(__AVR__)
	        strcpy_P(buff, (PGM_P)pgm_read_word(&(IntervalQualitiesNames[IntervalQuality])));
	    #else
	        strcpy(buff,IntervalQualitiesNames[IntervalQuality]);
	    #endif
	}
	else
	{
		buff[0] = '\0';
	}
	return buff;
}


const char* Flash::GetIntervalName(uint8_t IntervalType, uint8_t IntervalQuality)
{
	return GetIntervalName(buffer,IntervalType,IntervalQuality);
}

char* Flash::GetIntervalName(char* buff, uint8_t IntervalType, uint8_t IntervalQuality)
{
	if(GetIntervalSemitones(IntervalType,IntervalQuality) == InvalidInterval)
	{
		buff[0] = '\0';
	}
    else
    {
        GetIntervalQualityStr(buff,IntervalQuality);
        uint8_t offset = strlen(buff);
        buff[offset++] = ' ';
        GetGenericIntervalStr(&buff[offset],IntervalType);    
    }

    return buff;
}
