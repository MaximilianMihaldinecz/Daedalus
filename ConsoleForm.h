#pragma once
#include<string>

class ConsoleForm
{
protected:
	void DrawHeader();
	void DrawOptionsListDesription(std::string description);
	void DrawOptionsList(const std::string options[], const std::string description[], int length, bool divideLast);
	void AddEmptyLines(int amount);
	void AddSpaceCharacters(int amount);
	void MoveCursor(int x, int y);
	void ClearScreen();
	int GetSelection();

public:
	ConsoleForm();
	virtual int Draw() = 0;
	~ConsoleForm();
};

