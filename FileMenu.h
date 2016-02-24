#pragma once
#include "ConsoleForm.h"
#include<string>


class FileMenu :
	public ConsoleForm
{
public:
	FileMenu();
	virtual int Draw();
	std::string Draw(bool isLoad);
	std::string Draw(bool isLoad, bool errorMsg);
	void ConfirmSave();

	~FileMenu();
};

