#include "StringList.h"
#include "WrappedString.h"
#include<string>

using namespace std;

StringList::StringList()
{
	_Count = 0;
	_Start = NULL;
	_Last = NULL;
}

//Adds a string to the list
void StringList::Add(string str)
{
	if (_Start != NULL)
	{
		WrappedString* newitem = new WrappedString(str);
		_Last->SetNext(newitem);
		_Last = newitem;
		_Count++;
	}
	else
	{
		_Start = new WrappedString(str);
		_Last = _Start;
		_Count = 1;
	}
}

//Returns a string element on the given index
string StringList::Get(short index)
{
	WrappedString* current = _Start;

	for (int i = 0; i < index; i++)
	{		
		current = current->GetNext();
	}

	return current->GetValue();
}

//Returns the number of elements
short StringList::GetCount()
{
	return _Count;
}

//Returns an array of strings containing all the elements of the list
string* StringList::GetAll()
{
	string* result = NULL;
	if (_Count > 0)
	{
		result = new string[_Count];
		WrappedString* current = _Start;

		for (int i = 0; i < _Count; i++)
		{
			result[i] = current->GetValue();
			current = current->GetNext();
		}
	}	
	return result;
}

StringList::~StringList()
{
	if (_Count > 0)
	{
		if (_Start != NULL)
		{
			//This will delete ALL the elements one by one, due to the destructor in the WrapperString class
			delete _Start;
		}
	}
}
