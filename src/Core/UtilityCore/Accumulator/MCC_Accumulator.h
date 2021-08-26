#ifndef Accumulator_H
#define Accumulator_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>

	namespace MusicCompositionCore
    {
        namespace Core
        {
            namespace UtilityCore
            {
                template <typename DataType, typename Range = int8_t>
                class Element
                {
	                private:

	                	DataType _Data;
	                	Range _Counter;

	                public:

	                	Element()
	                	{
	                		_Counter = 0;
	                	}

	                	Element(const DataType& Src, const Range& Count)
	                	{
	                		_Data = Src;
	                		_Counter = Count;
	                	}

	                	void SetData(const DataType& Src)
	                	{
	                		_Data = Src;
	                	}

	                	void SetCounter(const Range& Count)
	                	{
	                		_Counter = Count;
	                	}

	                	const DataType& Data() const
	                	{
	                		return _Data;
	                	}

	                	const Range& Counter() const
	                	{
	                		return _Counter;
	                	}
                };

                template <typename DataType, typename Range = int8_t>
                int8_t ElementSorting(const Element<DataType,Range>& Compare, const Element<DataType,Range>& Pivot)
                {
	                if(Compare.Data()==Pivot.Data()){return CPVector::Sorting::Equal;}
	                else if(Compare.Data()<Pivot.Data()){return CPVector::Sorting::Swap;}
	                else{return CPVector::Sorting::Ignore;}
                }

                template <typename DataType, typename Range = int8_t>
                class Accumulator
                {
                	CPVector::vector<Element<DataType,Range>> _Elements;
                	Element<DataType,Range> _ElementBuffer;

	                public:
	                	
	                	Accumulator()
	                	{
	                		_Elements.resize(0);
	                	}

	                	Accumulator(const CPVector::vector<Element<DataType,Range>>& Source)
	                	{
	                		for(unsigned int i = 0; i < Source.size() ; i++)
	                		{
	                			AddElement(Source[i]);
	                		}
	                	}

	                	Accumulator(const CPVector::vector<DataType>& Source)
	                	{
	                		for(unsigned int i = 0; i < Source.size(); i++)
	                		{
	                			bool flag = 1;
	                			for(unsigned int j = 0; j < _Elements.size(); j++)
	                			{
	                				if(Source[i] == _Elements[j].Data())
	                				{
	                					_Elements[j].SetCounter( _Elements[j].Counter() + 1);
	                					flag = 0;
	                					j = _Elements.size();
	                				}
	                			}

	                			if(flag)
	                			{
	                				AddElement(Source[i]);
	                			}
	                		}
	                	}

	                	void Clear()
	                	{
	                		_Elements.resize(0);
	                	}

	                	Accumulator<DataType,Range>& operator+=(const Element<DataType,Range>& Data)
	                	{
	                		AddElement(Data);
	                		return (*this);
	                	}

	                	void AddElement(const Element<DataType,Range>& Source)
	                	{
	                		if(ElementExist(Source))
	                		{
	                			unsigned int Index = GetElementIndex(Source);
	                			_Elements[Index].SetCounter(_Elements[Index].Counter() + Source.Counter());
	                		}
	                		else
	                		{
	                			_Elements.push_back(Source);
	                			_Elements.Sort(ElementSorting<DataType,Range>);
	                		}
	                	}

	                	void AddElement(const DataType& Source, const Range& Counter = 1)
	                	{
	                		if(ElementExist(Source))
	                		{
	                			unsigned int Index = GetElementIndex(Source);
	                			_Elements[Index].SetCounter(_Elements[Index].Counter() + Counter);
	                		}
	                		else
	                		{
	                			_ElementBuffer.SetData(Source);
	                			_ElementBuffer.SetCounter(Counter);

	                			_Elements.push_back(_ElementBuffer);
	                			_Elements.Sort(ElementSorting<DataType,Range>);
	                		}
	                	}

	                	void RemoveElement(const Element<DataType,Range>& Source)
	                	{
	                		if(ElementExist(Source))
	                		{
	                			unsigned int Index = GetElementIndex(Source);
	                			_Elements[Index].SetCounter(_Elements[Index].Counter() - Source.Counter());
	                		}
	                		else
	                		{
	                			_ElementBuffer.SetData(Source);
	                			_ElementBuffer.SetCounter(Source.Counter()*-1);

	                			_Elements.push_back(_ElementBuffer);
	                			_Elements.Sort(ElementSorting<DataType,Range>);
	                		}
	                	}

	                	void RemoveElement(const DataType& Source, const Range& Counter = 1)
	                	{
	                		if(ElementExist(Source))
	                		{
	                			unsigned int Index = GetElementIndex(Source);
	                			_Elements[Index].SetCounter(_Elements[Index].Counter() - Counter);
	                		}
	                		else
	                		{
	                			_ElementBuffer.SetData(Source);
	                			_ElementBuffer.SetCounter(Counter*-1);

	                			_Elements.push_back(_ElementBuffer);
	                			_Elements.Sort(ElementSorting<DataType,Range>);
	                		}
	                	}

						bool ElementExist(const Element<DataType,Range>& Source)
	                	{
	                		for(uint8_t i = 0; i < _Elements.size(); i++)
	                		{
	                			if(Source.Data() == _Elements[i].Data())
	                			{
	                				return 1;
	                			}
	                		}
	                		return 0;
	                	}

						bool ElementExist(const DataType& Source)
	                	{
	                		for(uint8_t i = 0; i < _Elements.size(); i++)
	                		{
	                			if(Source == _Elements[i].Data())
	                			{
	                				return 1;
	                			}
	                		}
	                		return 0;
	                	}

	                	unsigned int GetElementIndex(const Element<DataType,Range>& Source)
	                	{
	                		for(uint8_t i = 0; i < _Elements.size(); i++)
	                		{
	                			if(Source.Data() == _Elements[i].Data())
	                			{
	                				return i;
	                			}
	                		}
	                		return -1;
	                	}

	                	unsigned int GetElementIndex(const DataType& Source)
	                	{
	                		for(uint8_t i = 0; i < _Elements.size(); i++)
	                		{
	                			if(Source == _Elements[i].Data())
	                			{
	                				return i;
	                			}
	                		}
	                		return -1;
	                	}

	                	unsigned int ElementCount()
	                	{
	                		return _Elements.size();
	                	}

	                	const Element<DataType,Range>& GetElement(const DataType& Source)
	                	{
	                		for(unsigned int i = 0; i < _Elements.size(); i++)
	                		{
	                			if(Source == _Elements[i].Data())
	                			{
	                				return _Elements[i];
	                			}
	                		}

	                		_ElementBuffer.SetData(Source);
	                		_ElementBuffer.SetCounter(0);

	                		return _ElementBuffer;
	                	}

	                	Element<DataType,Range>& ElementBuffer()
	                	{
	                		return _ElementBuffer;
	                	}

	                	Element<DataType,Range>& operator[](unsigned int Index)
                        {
                            if(Index < _Elements.size())
                            {
                            	return _Elements[Index];
                            }

                            _ElementBuffer.SetData(0);
                            _ElementBuffer.SetCounter(0);

                            return _ElementBuffer;
                        }

                        const Element<DataType,Range>& operator[](unsigned int Index) const
                        {
                            if(Index < _Elements.size())
                            {
                            	return _Elements[Index];
                            }

                            _ElementBuffer.SetData(0);
                            _ElementBuffer.SetCounter(0);

                            return _ElementBuffer;
                        }
                };
            }
        }
    }

#endif//Accumulator_H
