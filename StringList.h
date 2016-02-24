#pragma once
#include "WrappedString.h"

class StringList
{
private:
	WrappedString* _Start;
	WrappedString* _Last;
	short _Count;

public:
	StringList();
	short GetCount();
	std::string* GetAll();
	void Add(std::string str);
	std::string Get(short index);
	~StringList();
};

