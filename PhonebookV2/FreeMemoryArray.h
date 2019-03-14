#pragma once
#include <afxtempl.h>

template<class TYPE>
class CFreeMemoryArray : public CTypedPtrArray < CPtrArray, TYPE*>
{
	//Constructor/Destructor 
public:
	CFreeMemoryArray();

	virtual ~CFreeMemoryArray();

};

template<class TYPE>
CFreeMemoryArray<TYPE>::CFreeMemoryArray()
{

}

template<class TYPE>
CFreeMemoryArray<TYPE>::~CFreeMemoryArray()
{
	for (int i = 0; i < GetCount(); i++)
	{
		delete GetAt(i);
		RemoveAt(i);

	}

}