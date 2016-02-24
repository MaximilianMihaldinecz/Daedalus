#pragma once
#include<string>



class WrappedString
{
private:
	std::string _Value;
	WrappedString* _Next;
public:
	WrappedString();
	WrappedString(std::string value);
	std::string GetValue();
	void SetValue(std::string value);
	WrappedString* GetNext();
	void SetNext(WrappedString* next);
	~WrappedString();
};

