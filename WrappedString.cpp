#include "WrappedString.h"
#include<string>

using namespace std;

//Wrapper for a string. To be used in a linked list.
WrappedString::WrappedString()
{
	_Next = NULL;
	_Value = "";
}

WrappedString::WrappedString(string value)
{
	_Next = NULL;
	_Value = value;
}

string WrappedString::GetValue()
{
	return _Value;
}

void WrappedString::SetValue(string value)
{
	_Value = value;
}

void WrappedString::SetNext(WrappedString* next)
{
	_Next = next;
}

WrappedString* WrappedString::GetNext()
{
	return _Next;
}

WrappedString::~WrappedString()
{
	if (_Next != NULL)
	{
		delete _Next;
	}	
}
